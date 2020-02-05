#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPoint>
#include <QImage>
#include <iostream>
#include "idraw.h"

class Circle: public IDraw
{
private:
    QPoint center;
    int radius;
    int width;

    QVector<int> parseLine(QString line);

public:
    Circle();

    QPoint getCenter();

    int getRadius();

    int getWidth();

    void setCenter(int x, int y);

    void setRadius(int rad);

    void setWidth(int wh);

    void clear();

    void draw(QImage& image);

    void writeToFile(QTextStream &stream);

    IDraw* readFromFile(QTextStream &stream);

    ~Circle();

};

#endif // CIRCLE_H
