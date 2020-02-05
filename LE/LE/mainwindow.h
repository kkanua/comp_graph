#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>
#include <QImage>

#include "polyline.h"
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QImage *image;
    QPixmap pixmap;
    Scene toDraw;
    QTimer timer;
    bool leftWasPressed;
    bool deleteAllowed;


public:
    MainWindow(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void drawLine(QPoint start, QPoint end);

    void drawScene();

    ~MainWindow();

private slots:
    void on_actionNew_file_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_2_triggered();

    void on_actionAbout_triggered();

    void on_actionDelete_last_polyline_triggered();
};
#endif // MAINWINDOW_H
