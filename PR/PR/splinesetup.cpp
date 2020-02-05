#include "splinesetup.h"
#include "ui_splinesetup.h"
#include <iostream>
#include <QPoint>

SplineSetup::SplineSetup(QWidget *parent): QDialog(parent), ui(new Ui::SplineSetup){
    ui->setupUi(this);
    this->setFixedSize(810, 610);
    image = new QImage(800, 600, QImage::Format_RGB32);
    image->fill(Qt::white);
    connect(this, SIGNAL(upd()), this, SLOT(update()));
    minX = -1.;
    maxX = 1.;
    minY = -1.;
    maxY = 1.;
    pointMoveIdx = -1;
}

void SplineSetup::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainter pt(image);
    pt.drawLine(0, image->height() / 2., image->width(), image->height() / 2.);
    pt.drawLine(image->width() / 2., 0, image->width() / 2., image->height());
    for(QVector2D pnt: tmp)
        pt.drawEllipse(QPoint(pnt.x(), pnt.y()), 10, 10);
    painter.drawImage(0, 0, *image);
}

void SplineSetup::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        points.append(QVector2D(event->x() - image->width() / 2., event->y() - image->height() / 2.));
        tmp.append(QVector2D(event->x(), event->y()));
        image->setPixel(event->x(), event->y(), Qt::black);
        redrawSpline();
        emit upd();
    }
    else if(event->button() == Qt::RightButton){
        QVector2D press = QVector2D(event->x() - image->width() / 2., event->y() - image->height() / 2.);
        for(int i = 0; i != points.length(); i++){
            if(press.distanceToPoint(points[i]) < 10)
                pointMoveIdx = i;
        }
    }
}

void SplineSetup::mouseMoveEvent(QMouseEvent *event){
    if(pointMoveIdx == -1)
        return;
    points[pointMoveIdx].setX(event->x() - image->width() / 2.);
    points[pointMoveIdx].setY(event->y() - image->height() / 2.);
    tmp[pointMoveIdx].setX(event->x());
    tmp[pointMoveIdx].setY(event->y());
    redrawSpline();
}

void SplineSetup::mouseReleaseEvent(QMouseEvent *event){
    pointMoveIdx = -1;
}

void SplineSetup::clear(){
    points.clear();
    tmp.clear();
    image->fill(Qt::white);
}

QVector<QVector2D> SplineSetup::getPoints(){
    return points;
}

void SplineSetup::redrawSpline(){
    if(tmp.length() > 4){
        image->fill(Qt::white);
        Spline::draw(tmp, *image);
        emit upd();
    }
}

QVector2D SplineSetup::getPointFromGlobal(QVector2D &vector){
    return vector;
}

SplineSetup::~SplineSetup(){
    delete image;
    delete ui;
}

QVector3D SplineSetup::getMove(){
    return move;
}

double SplineSetup::getScale(){
    return scale;
}

void SplineSetup::on_buttonBox_accepted()
{
    scale = ui->scale_SpinBox->value();
    move.setX(ui->x_SpinBox->value() / 10.);
    move.setY(ui->y_SpinBox->value() / 10.);
    move.setZ(ui->z_SpinBox->value() / 10.);
    emit splineReady();
}
