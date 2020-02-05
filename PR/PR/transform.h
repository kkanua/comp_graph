#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector4D>
#include <QMatrix4x4>
#include <math.h>

class Transform
{
public:
    Transform();

//    static QMatrix4x4 rotate(QVector4D& vector, int axis, double angle);

    static QMatrix4x4 getRotateMatrix(int axis, double angle);

    static QMatrix4x4 scale(float sx, float sy, float sz);

    static void matrixTransform(QMatrix4x4& matrix, QVector4D& vector);

    static QMatrix4x4 perspective(float zn, float zf, float sw, float sh);

    static QMatrix4x4 move(float dx, float dy, float dz);

    static QMatrix4x4 camera();

};

#endif // TRANSFORM_H
