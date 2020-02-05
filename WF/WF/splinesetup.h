#ifndef SPLINESETUP_H
#define SPLINESETUP_H

#include <QDialog>
#include <QImage>
#include <QVector>
#include <QVector2D>
#include <QPainter>
#include <QMouseEvent>

#include "spline.h"

namespace Ui{class SplineSetup;}

class SplineSetup : public QDialog
{
    Q_OBJECT

private:
    Ui::SplineSetup *ui;
    QImage* image;
    QVector<QVector2D> points;
    QVector<QVector2D> tmp;
    QVector3D move;
    double scale;
    float minX, maxX, minY, maxY;
    int pointMoveIdx;

Q_SIGNALS:
    void upd();

    void splineReady();

public:
    explicit SplineSetup(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void redrawSpline();

    QVector2D getPointFromGlobal(QVector2D& vector);

    void clear();

    QVector3D getMove();

    double getScale();

    QVector<QVector2D> getPoints();

    ~SplineSetup();

private slots:
    void on_buttonBox_accepted();
};

#endif // SPLINESETUP_H
