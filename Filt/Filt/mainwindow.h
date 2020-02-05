#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QFileDialog>
#include <QSlider>
#include <QScreen>
#include <iostream>
#include <QTime>
#include <QDate>

#include "scene.h"
#include "matrixsetup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QImage *backgroundSrcImg;
    QImage *backgroundDstImg;
    QImage *srcImg;
    QImage *dstImg;
    Scene *scene;
    matrixSetup *matrixWindow;
    int counter;

public:
    MainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    void resizeEvent(QResizeEvent *event);

    ~MainWindow();

public slots:
    void matrixFilt();

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionMove_dst_to_src_triggered();
    void on_actionCopy_src_to_dst_triggered();
    void on_blackWhite_clicked();
    void on_negative_clicked();
    void on_sharp_clicked();
    void on_blur_clicked();
    void on_aquarel_clicked();
    void on_emboss_clicked();
    void on_pthSelection_clicked();
    void on_sliderPSelect_valueChanged(int value);

    void on_gamma_clicked();
    void on_doubleSpinBox_valueChanged(double arg1);
    void on_ident_clicked();
    void on_custom_clicked();
};
#endif // MAINWINDOW_H
