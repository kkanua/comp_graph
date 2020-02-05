#include "quadrangle.h"

quadrangle::quadrangle(){

}

quadrangle::quadrangle(QVector4D a, QVector4D b, QVector4D c, QVector4D d){
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

QVector4D quadrangle::getNormal(){
    return QVector4D();
}
