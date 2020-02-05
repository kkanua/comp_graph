#include "spline.h"

#include <iostream>

Spline::Spline(){
    M_s = QMatrix4x4(-1., 3., -3., 1.,
                      3., -6., 3., 0.,
                     -3., 0., 3., 0.,
                      1., 4., 1., 0.) * 1 / 6.;


//    points.append(QVector2D(0.1, -0.5));
//    points.append(QVector2D(0.1, -0.2));
//    points.append(QVector2D(0.2, 0.01));
//    points.append(QVector2D(0.2, 0.52));
//    points.append(QVector2D(0.3, 0.7));
//    points.append(QVector2D(0.3, 0.8));

    // THIS SHOULD BE OK
//    points.append(QVector2D(1. / 2., 1. / 2.));
//    points.append(QVector2D(2. / 2., 2. / 2.));
//    points.append(QVector2D(3. / 2., 4. / 2.));
//    points.append(QVector2D(4. / 2., 6. / 2.));
//    points.append(QVector2D(5. / 2., 7. / 2.));
//    points.append(QVector2D(8. / 2., 8. / 2.));
//    points.append(QVector2D(9. / 2., 9. / 2.));
//    points.append(QVector2D(10. / 2., 10. / 2.));
    // STOP

//    points.append(QVector2D(10., 400.));
//    points.append(QVector2D(100., 100.));
//    points.append(QVector2D(150., 290.));
//    points.append(QVector2D(200., 380.));
//    points.append(QVector2D(250., 470.));
//    points.append(QVector2D(300., 550.));

//    points.append(QVector2D(10., 50.));
//    points.append(QVector2D(50., 50.));
//    points.append(QVector2D(50., 150.));
//    points.append(QVector2D(50., 250.));
//    points.append(QVector2D(50., 350.));
//    points.append(QVector2D(50., 450.));
//    points.append(QVector2D(70., 470.));
//    points.append(QVector2D(100., 550.));
//    points.append(QVector2D(120., 560.));
}

Spline::Spline(QVector<QVector2D> pts){
    M_s = QMatrix4x4(-1., 3., -3., 1.,
                      3., -6., 3., 0.,
                     -3., 0., 3., 0.,
                      1., 4., 1., 0.) * 1 / 6.;
    angle = 0.;
    scale = 1.;
    points = pts;
}

void Spline::setVectorData(QVector4D &vector, float x, float y, float z, float w){
    vector.setX(x);
    vector.setY(y);
    vector.setZ(z);
    vector.setW(w);
}

void Spline::setVector(QVector4D &vector, float x, float y, float z, float w){
    vector.setX(x);
    vector.setY(y);
    vector.setZ(z);
    vector.setW(w);
}

QVector2D Spline::getPoint(float t, int currentPoint){
    QVector4D T(t*t*t, t*t, t, 1.);
    QVector4D G_sx(points[currentPoint - 1].x(), points[currentPoint].x(), points[currentPoint + 1].x(),points[currentPoint + 2].x());
    QVector4D G_sy(points[currentPoint - 1].y(), points[currentPoint].y(), points[currentPoint + 1].y(),points[currentPoint + 2].y());
    QVector4D temp = T * M_s;
    return QVector2D(QVector4D::dotProduct(temp, G_sx), QVector4D::dotProduct(temp, G_sy));
}

void Spline::draw(QVector<QVector2D>& points, QImage &image){
    QPainter painter(&image);
    QMatrix4x4 M_s = QMatrix4x4(-1.,  3., -3., 1.,
                                 3., -6.,  3., 0.,
                                -3.,  0.,  3., 0.,
                                 1.,  4.,  1., 0.) * 1 / 6.;
    QVector4D T;
    QVector4D G_sx;
    QVector4D G_sy;
    QVector4D temp;
    float x_prev = -1, y_prev = -1;
    for(int i = 1; i != points.length() - 2; i++){
        for(double t = 0; t <= 1; t += 0.1){
            setVector(T, t*t*t, t*t, t, 1.);
            setVector(G_sx, points[i - 1].x(), points[i].x(), points[i + 1].x(),points[i + 2].x());
            setVector(G_sy, points[i - 1].y(), points[i].y(), points[i + 1].y(),points[i + 2].y());
            temp = T * M_s;
            if(x_prev != -1 && y_prev != -1)
                painter.drawLine(QVector4D::dotProduct(temp, G_sx), QVector4D::dotProduct(temp, G_sy), x_prev, y_prev);
            x_prev = QVector4D::dotProduct(temp, G_sx);
            y_prev = QVector4D::dotProduct(temp, G_sy);
        }
    }
}

int Spline::pointsSize(){
    return points.length();
}
