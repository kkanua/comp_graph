#ifndef GLOBALSCENE_H
#define GLOBALSCENE_H

#include <QVector>
#include <QImage>
#include <QWidget>
#include <QMatrix4x4>
#include <QFile>
#include "spline.h"
#include "transform.h"
#include "camera.h"

class GlobalScene: public QWidget{
    Q_OBJECT
private:
    QVector<Spline> splines;
    QVector<float> scales;
    QVector<QVector3D> moves;
    Camera camera;
    int k, n;
    QMatrix4x4 rot_mat;

Q_SIGNALS:
    void redraw();

public:
    GlobalScene();

    void draw(QImage& image);

    void setVectorData(QVector4D& vector, float x, float y, float z, float w);

    void addSpline(Spline spline, double scaleFactor, QVector3D move);

    void rotate(QImage& image, double angle_x, double angle_y, double angle_z);

    void drawBox(QImage& image, QMatrix4x4& matrix);

    QMatrix4x4 toScreen(int width, int height);

    void setZn(double val, QImage& image);

    void setZf(double val, QImage& image);

    void setSw(double val, QImage& image);

    void setSh(double val, QImage& image);

    void setK(int k_new, QImage& image);

    void setN(int n_new, QImage& image);

    void changePos(int obj, double x, double y, double z, QImage& image);

    void changeScale(int obj, double scale, QImage& image);

    bool inRange(QVector4D& vector);

    QVector<float> getMaxandMins();

    void readFile(QString filename, QImage& image);

    QVector<float> parseArgs(QString line);

};

#endif // GLOBALSCENE_H
