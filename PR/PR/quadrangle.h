#ifndef QUADRANGLE_H
#define QUADRANGLE_H

#include <QVector4D>

class quadrangle
{
public:
    QVector4D a, b, c, d;
    QVector4D normal;

    quadrangle();

    quadrangle(QVector4D a, QVector4D b, QVector4D c, QVector4D d);

    QVector4D getNormal();
};

#endif // QUADRANGLE_H
