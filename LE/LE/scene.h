#ifndef SCENE_H
#define SCENE_H

#include "polyline.h"
#include <QVector>
#include <QFile>
#include <iostream>
#include <QTextStream>

class Scene
{
private:
    QVector<Polyline> scenePL;
    Polyline tempPolyline;
    QString currentFile;

public:

    Scene();

    QVector<Polyline>& getScene();

    void addTempCoordinates(int x, int y);

    void addTempCoordinates(QPoint point);

    void resetTempPolyline();

    void saveTempPolyline();

    void removeLastTempCoordinates();

    bool readFile(QString filename);

    bool createNewProject(QString filename);

    bool save();

    bool saveAs(QString filename);

    void resetScene();

    void removeLastPolyline();

    bool isEmptyFile();

    void open(QString filename);

    QPoint getCoordinatesFromStr(QString& str);

    Polyline getTempPolyline();

};

#endif // SCENE_H
