#ifndef SPLINE_H
#define SPLINE_H

#include <QVector2D>
#include <QVector>
#include <QImage>
#include <QMatrix4x4>
#include <QPainter>
#include <math.h>

#include "transform.h"

class Spline{
private:
    QVector<QVector2D> points;
    QMatrix4x4 M_s;
    double angle, scale;

public:
    Spline();

    Spline(QVector<QVector2D> pts);

    QVector<QVector2D> getPoints();

    void draw(QImage& image);

    void setVectorData(QVector4D& vector, float x, float y, float z, float w);

    QVector2D getPoint(float t, int currentPoint);

    static void setVector(QVector4D& vector, float x, float y, float z, float w);

    static void draw(QVector<QVector2D>& points, QImage& image);

    int pointsSize();

};

#endif // SPLINE_H
