#ifndef CAMERA_H
#define CAMERA_H

#include <QVector4D>


class Camera
{
private:
    QVector4D c;
    QVector4D v;
    QVector4D u;
    float zn, zf;
    float sw, sh;

public:
    Camera();

    void setVector(QVector4D& vector, float x, float y, float z, float w);

    QVector4D getC();

    QVector4D getV();

    QVector4D getU();

    float getZn();

    float getZf();

    float getSw();

    float getSh();

    void setZn(double val);

    void setZf(double val);

    void setSw(double val);

    void setSh(double val);
};

#endif // CAMERA_H
