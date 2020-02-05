#ifndef SCENE_H
#define SCENE_H

#include <QImage>
#include <QFile>
#include <QTextStream>
#include <iostream>

#include "legend.h"
#include "colormap.h"
#include "function.h"

class Scene
{
private:
    ColorMap map;
    Legend legend;
    Function f;

public:
    Scene();

    void drawColorMap(QImage& image, QImage& imageVals);

    void drawInterpolationMap(QImage& image);

    void drawDitheringMap(QImage& image);

    void drawInterpolationLeg(QImage& image);

    void drawDitheringLeg(QImage& image);

    void updateParametrs(QVector<double> params);

    void recalculateMap(QImage& image, QImage& imageVals);

    void recalculateLeg(QImage& image, QImage& imageVals);

    void drawLegend(QImage& image, QImage& imageVals);

    void drawIsolinesMap(QImage& image);

    void drawIsolinesLeg(QImage& image);

    void drawIsoline(QImage& image, double isoline);

    double getX(int u, QImage& image);

    double getY(int v, QImage& image);

    double getFvalue(double x, double y);

    void drawGrid(QImage& image);

    void readFile(QString filename);

    QVector<double> parseArgs(QString line);
};

#endif // SCENE_H
