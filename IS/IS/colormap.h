#ifndef COLORMAP_H
#define COLORMAP_H

#include <QImage>
#include <QVector>
#include <QPoint>
#include <math.h>
#include <QPainter>

#include "function.h"

class ColorMap
{
private:
    int numOfValues;

    int net_k;
    int net_m;
    double maxX;
    double minX;
    double maxY;
    double minY;
    QVector<double> isolinesLevels;
    QVector<QColor> colors;
    bool isDithered;
    bool isInterpolated;
    QColor isoColor;


    int u(double x, QImage& image);

    int v(double y, QImage& image);

    QVector<double> maxAndMin(QImage& image, double(*f)(double, double));

    void setIsolinesLevels(double min, double max);

    int getIsolineIdx(double f_value);

public:
    ColorMap();

    double x(int u, QImage& image);

    double y(int v, QImage& image);

    void draw(QImage& image, QImage& imageVals, double(*f)(double, double));

    void setParams(QVector<double> params);

    void recalculate(QImage& image, QImage& imageVals, double(*f)(double, double));

    void drawIsoline(QImage& image, QVector<double> isolines, double(*f)(double, double));

    void drawInterpolation(QImage& image, bool dithering, double(*f)(double, double));

    QVector<double> getIsolineLevels(QImage& image, double(*f)(double, double));

    void drawGrid(QImage& image);

    void setNumberOfLevels(int num);

    void setColors(QVector<QColor> col);

    void setIsoColor(QColor color);
};

#endif // COLORMAP_H
