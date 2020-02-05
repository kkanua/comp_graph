#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define IMAGE_WIDTH 400
#define IMAGE_HEIGHT 400

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <iostream>

#include "scene.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    Dialog *window;
    QImage *imageColorMap;
    QImage *imageLegend;
    QImage *imageIsolinesMap;
    QImage *imageIsolinesLeg;
    QImage *imageMapVals;
    QImage *imageLegVals;
    Scene scene;
    bool isIsolines;
    bool isGrid;
    bool wasPressed;
    bool isDithering;
    bool isInterpolated;

public:
    MainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);

    void setImageBorders();

    ~MainWindow();

Q_SIGNALS:
    void upd();

public slots:
    void setParams();

private slots:
    void on_pushButton_clicked();
    void on_interpolation_clicked(bool checked);
    void on_dither_clicked(bool checked);
    void on_isolines_clicked();
    void on_grid_clicked();
    void on_map_clicked();
};
#endif // MAINWINDOW_H
