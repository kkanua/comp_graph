#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include <QObject>
#include <math.h>

#include "polygon.h"
#include "circle.h"
#include "fill.h"
#include "idraw.h"

class Scene: public QObject
{
    Q_OBJECT
private:
    QVector<IDraw*> sceneElements;
    Circle tempCircle;
    Polygon tempPolygon;
    QString currentFile;

public:
    Scene();

    QVector<IDraw*>& getSceneElements();

    void addTempPolygonPoint(int x, int y);

    void addTempCircle(int x, int y, int radius);

    void saveTempCircle();

    void saveTempPolygon();

    void setTempCircleRadiusTo(int x, int y);

    void removeLastPolygonPoint();

    void setFill4(int x, int y, int color);

    void setFill8(int x, int y, int color);

    void setTempPolygonWidth(int width);

    Circle getTempCircle();

    Polygon getTempPolygon();

    void resetScene();

    bool readFile(QString filename);

    bool createNewProject(QString filename);

    bool save();

    QString getCurrentFilename();

    bool open(QString filename);

    bool saveAs(QString filename);

    IDraw* getLastElem();
    
    void fixBorders(int& x, int& y);

    ~Scene();

Q_SIGNALS:
    void tempUpdated();

    void permanentUpdated();

    void redrawAll();
};

#endif // SCENE_H
