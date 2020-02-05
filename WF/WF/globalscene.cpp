#include "globalscene.h"
#include <iostream>

GlobalScene::GlobalScene(){
    rot_mat = QMatrix4x4(1., 0., 0., 0.,
                         0., 1., 0., 0.,
                         0., 0., 1., 0.,
                         0., 0., 0., 1.);
    k = 5;
    n = 5;
}

void GlobalScene::addSpline(Spline spline, double scaleFactor, QVector3D move){
    splines.append(spline);
    scales.append(scaleFactor);
    moves.append(move);
}

void GlobalScene::draw(QImage &image){
    image.fill(Qt::white);


    QVector<float> minAndMaxs = getMaxandMins();
    float scaleFactor = std::max({(minAndMaxs[1] - minAndMaxs[0]) / 2., (minAndMaxs[3] - minAndMaxs[2]) / 2.,(minAndMaxs[5] - minAndMaxs[4]) / 2.});

    QMatrix4x4 TransformToBox;
    QMatrix4x4 BoxTransform = toScreen(image.width(), image.height()) *
            Transform::perspective(camera.getZn(), camera.getZf(), camera.getSw(), camera.getSh()) *
            Transform::camera() *
            rot_mat;

    QVector<QMatrix4x4> transforms;
    for(int i = 0; i != moves.length(); i++){
        TransformToBox = Transform::move(moves[i].x(), moves[i].y(), moves[i].z()) *
                         Transform::scale( 1. / scaleFactor * scales[i], 1. / scaleFactor * scales[i], 1. / scaleFactor * scales[i]) *
                         Transform::move(-(minAndMaxs[1] + minAndMaxs[0]) / 2, -(minAndMaxs[3] + minAndMaxs[2]) / 2, -(minAndMaxs[5] + minAndMaxs[4]) / 2);
        transforms.append(BoxTransform * TransformToBox);
    }



    drawBox(image, BoxTransform);

    int counter1 = 0, counter2 = 0;
    for(int q = 0; q != splines.length(); q++){
        QVector2D pt;
        QPainter painter(&image);
        QVector<QVector4D> prev_line, temp_line;
        QVector4D r, r_prev, r_first;

        for(int i = 1; i != splines[q].pointsSize() - 2; i++){
            counter2 = 0;
            for(double t = 0; t <= 1; t += 0.1){
                setVectorData(r_prev, 0., 0., 0., 0.);
                pt = splines[q].getPoint(t, i);
                counter1 = 0;
                for(double phi = 0; phi <= 2 * M_PI; phi += 0.1){
                    setVectorData(r, pt.x() * cos(phi), pt.x() * sin(phi), pt.y(), 1.);
                    Transform::matrixTransform(transforms[q], r);
                    setVectorData(r, r.x() / r.w(), r.y() / r.w(), r.z() / r.w(), 1.);
//                    if(r.z() > 1 || r.z() < 0)
//                        continue;
                    if(r_prev.isNull())
                        r_first = r;
                    if(counter2 % this->k == 0 && !r_prev.isNull())
                        painter.drawLine(r.x(), r.y(), r_prev.x(), r_prev.y());

                    r_prev = r;
                    if(!prev_line.isEmpty() && counter1 % this->n == 0)
                        painter.drawLine(r.x(), r.y(), prev_line[temp_line.length()].x(), prev_line[temp_line.length()].y());
                    counter1++;
                    temp_line.append(r);
                }
                if(counter2 % this->k == 0)
                    painter.drawLine(r.x(), r.y(), r_first.x(), r_first.y());
                prev_line = temp_line;
                temp_line.clear();
                counter2++;
            }
        }
    }
    emit redraw();
}

void GlobalScene::drawBox(QImage &image, QMatrix4x4& matrix){
    QPainter editor(&image);
    QVector4D A = QVector4D(-1, -1, -1, 1);
    Transform::matrixTransform(matrix, A);
    QVector4D B = QVector4D(-1, -1, 1, 1);
    Transform::matrixTransform(matrix, B);
    QVector4D C = QVector4D(1, -1, -1, 1);
    Transform::matrixTransform(matrix, C);
    QVector4D D = QVector4D(1, -1, 1, 1);
    Transform::matrixTransform(matrix, D);
    QVector4D A_ = QVector4D(-1, 1, -1, 1);
    Transform::matrixTransform(matrix, A_);
    QVector4D B_ = QVector4D(-1, 1, 1, 1);
    Transform::matrixTransform(matrix, B_);
    QVector4D C_ = QVector4D(1, 1, -1, 1);
    Transform::matrixTransform(matrix, C_);
    QVector4D D_ = QVector4D(1, 1, 1, 1);
    Transform::matrixTransform(matrix, D_);
    A = A / A.w();
    B = B / B.w();
    C = C / C.w();
    D = D / D.w();
    A_ = A_ / A_.w();
    B_ = B_ / B_.w();
    C_ = C_ / C_.w();
    D_ = D_ / D_.w();
    editor.drawLine(A.x(), A.y(), B.x(), B.y());
    editor.drawLine(A.x(), A.y(), C.x(), C.y());
    editor.drawLine(A.x(), A.y(), A_.x(), A_.y());
    editor.drawLine(B.x(), B.y(), D.x(), D.y());
    editor.drawLine(B.x(), B.y(), B_.x(), B_.y());
    editor.drawLine(C.x(), C.y(), D.x(), D.y());
    editor.drawLine(C.x(), C.y(), C_.x(), C_.y());
    editor.drawLine(D.x(), D.y(), D_.x(), D_.y());
    editor.drawLine(A_.x(), A_.y(), B_.x(), B_.y());
    editor.drawLine(A_.x(), A_.y(), C_.x(), C_.y());
    editor.drawLine(D_.x(), D_.y(), C_.x(), C_.y());
    editor.drawLine(D_.x(), D_.y(), B_.x(), B_.y());
}

void GlobalScene::setVectorData(QVector4D &vector, float x, float y, float z, float w){
    vector.setX(x);
    vector.setY(y);
    vector.setZ(z);
    vector.setW(w);
}

void GlobalScene::rotate(QImage& image, double angle_x, double angle_y, double angle_z){
    rot_mat = Transform::getRotateMatrix(2, -angle_x) * Transform::getRotateMatrix(1, angle_z) * rot_mat;
    draw(image);
}

QMatrix4x4 GlobalScene::toScreen(int width, int height){
    float w = (width - 1) / 2;
    float h = (height - 1) / 2;
    QMatrix4x4 screen = {
        w,     0.f,    0.f,    w,
        0.f,    -h,    0.f,    h,
        0.f,   0.f,    1.f,    0,
        0,       0,    0.f,    1.f
    };
    return screen;
}

void GlobalScene::setZn(double val, QImage& image){
    camera.setZn(val);
    draw(image);
}

void GlobalScene::setZf(double val, QImage& image){
    camera.setZf(val);
    draw(image);
}

void GlobalScene::setSw(double val, QImage& image){
    camera.setSw(val);
    draw(image);
}

void GlobalScene::setSh(double val, QImage& image){
    camera.setSh(val);
    draw(image);
}

void GlobalScene::setK(int k_new, QImage& image){
    this->k = k_new;
    draw(image);
}

void GlobalScene::setN(int n_new, QImage& image){
    this->n = n_new;
    draw(image);
}

void GlobalScene::changePos(int obj, double x, double y, double z, QImage& image){
    moves[obj].setX(x);
    moves[obj].setY(y);
    moves[obj].setZ(z);
    draw(image);
}

void GlobalScene::changeScale(int obj, double scale, QImage& image){
    scales[obj] = scale;
    draw(image);
}

bool GlobalScene::inRange(QVector4D &vector){
    if(abs(vector.x()) <= 1 && abs(vector.y()) <= 1 && abs(vector.z()) <= 1)
        return true;
    return false;
}

QVector<float> GlobalScene::getMaxandMins(){
    float min_x = 10000, max_x = -10000;
    float min_y = 10000, max_y = -10000;
    float min_z = 10000, max_z = -10000;
    QVector4D vector;
    for (Spline spline: splines) {
        for(int i = 1; i != spline.pointsSize() - 2; i++){
            for(double t = 0; t <= 1; t += 0.1){
                QVector2D pt = spline.getPoint(t, i);
                for(double phi = 0; phi <= 2 * M_PI; phi += 0.1){
                    setVectorData(vector, pt.x() * cos(phi), pt.x() * sin(phi), pt.y(), 1.);
                    min_x = std::min(vector.x(), min_x);
                    min_y = std::min(vector.y(), min_y);
                    min_z = std::min(vector.z(), min_z);
                    max_x = std::max(vector.x(), max_x);
                    max_y = std::max(vector.y(), max_y);
                    max_z = std::max(vector.z(), max_z);
                }
            }
        }
    }
    return {min_x, max_x, min_y, max_y, min_z, max_z};
}

void GlobalScene::readFile(QString filename, QImage& image){
    QFile file(filename);
    QVector<float> data;
    QVector<QVector2D> pts;
    if(!file.open(QIODevice::ReadWrite))
        return ;
    QTextStream stream(&file);
    QString line;
    line = stream.readLine();
    data = parseArgs(line);
    setN(data[0], image);
    setK(data[1], image);
    setZn(data[2], image);
    setZf(data[3], image);
    setSw(data[4], image);
    setSh(data[5], image);
    data.clear();
    while(!stream.atEnd()){
        line = stream.readLine();
        data = parseArgs(line);
        if(data.length() == 1 && pts.length() != 0){
            addSpline(Spline(pts), 1., {0., 0., 0.});
            pts.clear();
            continue;
        }
        if(data.length() != 1)
            pts.append({data[0], data[1]});
    }
    addSpline(Spline(pts), 1., {0., 0., 0.});
    draw(image);
}

QVector<float> GlobalScene::parseArgs(QString line){
    QVector<float> vals;
        QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        for(QString str: list)
            vals.append(str.toDouble());
        return vals;
}
