#include "camera.h"

Camera::Camera(){
    setVector(c, -10, 0, 0, 1);
    setVector(v, 10, 0, 0, 1);
    setVector(u, 0, 1, 0, 1);

    zn = 0;
    zf = 1;
    sw = 1;
    sh = 1;
}

QVector4D Camera::getC(){
    return c;
}

QVector4D Camera::getV(){
    return v;
}

QVector4D Camera::getU(){
    return u;
}

float Camera::getSh(){
    return sh;
}

float Camera::getSw(){
    return sw;
}

float Camera::getZf(){
    return zf;
}

float Camera::getZn(){
    return zn;
}

void Camera::setZn(double val){
    zn = val;
}

void Camera::setZf(double val){
    zf = val;
}

void Camera::setSw(double val){
    sw = val;
}

void Camera::setSh(double val){
    sh = val;
}


void Camera::setVector(QVector4D &vector, float x, float y, float z, float w){
    vector.setX(x);
    vector.setY(y);
    vector.setZ(z);
    vector.setW(w);
}
