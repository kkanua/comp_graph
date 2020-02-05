#include "transform.h"

Transform::Transform(){

}

QMatrix4x4 Transform::getRotateMatrix(int axis, double angle){
    QMatrix4x4 rotate;
    switch (axis) {
        case 0:
            rotate = QMatrix4x4( 1.,        0.,          0,      0.,
                                 0.,    cos(angle),  sin(angle), 0.,
                                 0.,   -sin(angle),  cos(angle), 0.,
                                 0.,        0.,          1.,     0.);
            break;

        case 1:
            rotate = QMatrix4x4(cos(angle),  0., sin(angle), 0.,
                                    0.,      1.,     0,      0.,
                               -sin(angle),  0., cos(angle), 0.,
                                    0.,      0.,     0.,     1.);
            break;

        case 2:
            rotate = QMatrix4x4(cos(angle),  sin(angle), 0., 0.,
                               -sin(angle),  cos(angle), 0,  0.,
                                    0.,          0.,     1., 0.,
                                    0.,          0.,     0., 1.);
            break;
    }

    return rotate;
}

QMatrix4x4 Transform::perspective(float zn, float zf, float sw, float sh){
//    QMatrix4x4 persp =  {
//                            2 * zf / sw,    0,           0,                0,
//                                  0, 2 * zf / sh,        0,                0,
//                                  0,        0,    zf / (zn - zf),  zn * zf / (zn - zf),
//                                  0,        0,          -1.,               1.
//                        };
        QMatrix4x4 persp =  {
                                      1,        0,    0,  0,
                                      0,        1,    0,  0,
                                      0,        0,    1,  0,
                                      0,        0,   0.3, 1.
                            };
    return persp;
}

QMatrix4x4 Transform::camera(){
    QVector3D ref(10, 0, 0);
    QVector3D eye(-10, 0, 0);
    QVector3D up(0, 1, 0);
    QVector3D w(eye - ref);
    w.normalize();
    QVector3D u(QVector3D::crossProduct(up, w));
    u.normalize();
    QVector3D v(QVector3D::crossProduct(w, u));
    return QMatrix4x4(
                u[0], u[1], u[2], 0,
                v[0], v[1], v[2], 0,
                w[0], w[1], w[2], 0,
                0   , 0   , 0   , 1
            )
            *
            QMatrix4x4(
                1, 0, 0, -eye[0],
                0, 1, 0, -eye[1],
                0, 0, 1, -eye[2],
                0, 0, 0, 1
            );
}

QMatrix4x4 Transform::move(float dx, float dy, float dz){
    return QMatrix4x4(1.f,    0.f,    0.f,    dx,
                      0.f,    1.f,    0.f,    dy,
                      0.f,    0.f,    1.f,    dz,
                      0.f,    0.f,    0.f,    1.f);
}

QMatrix4x4 Transform::scale(float sx, float sy, float sz){
    QMatrix4x4 scale(  sx, 0., 0., 0.,
                       0., sy, 0., 0.,
                       0., 0., sz, 0.,
                       0., 0., 0., 1.);
    return scale;
}

void Transform::matrixTransform(QMatrix4x4 &matrix, QVector4D &vector){
    vector = matrix * vector;
}
