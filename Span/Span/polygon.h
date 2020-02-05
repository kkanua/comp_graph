#ifndef POLYGON_H
#define POLYGON_H

#include <QVector>
#include <QPoint>
#include <QImage>
#include <math.h>
#include "idraw.h"

class Polygon: public IDraw
{
private:
    QVector<QPoint> polygonCoordinates;

    int width;

    void drawLine(QPoint start, QPoint end, QImage& image);

    void colorNeighbour(int x, int y, int dx, int dy, QImage& image);

    QPoint parseLine(QString line);

public:
    Polygon();

    Polygon(QVector<QPoint> points);

    QVector<QPoint> getPolygonCoordinates();

    void addPoint(int x, int y);

    void setWidth(int wh);

    void removeLastPoint();

    int getWidth();

    void clear();

    void draw(QImage& image);

    void writeToFile(QTextStream &stream);

    IDraw * readFromFile(QTextStream &stream);

    ~Polygon();

};

#endif // POLYGON_H
