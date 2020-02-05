#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QMatrix4x4>

#include "spline.h"
#include "globalscene.h"
#include "splinesetup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QImage* image;
    GlobalScene globalScene;
    SplineSetup* spSetupWindow;
    QMatrix4x4 rotate;
    Spline spline;
    bool wasPressed;
    int x_prev, y_prev;

public:
    MainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    ~MainWindow();

public slots:
    void addSpline();

private slots:
    void on_spline_setup_clicked();
    void on_zn_SpinBox_valueChanged(double arg1);
    void on_zf_SpinBox_valueChanged(double arg1);
    void on_sw_SpinBox_valueChanged(double arg1);
    void on_sh_SpinBox_valueChanged(double arg1);

    void on_n_spinBox_valueChanged(int arg1);
    void on_k_spinBox_valueChanged(int arg1);
    void on_x_SpinBox_valueChanged(double arg1);
    void on_y_SpinBox_valueChanged(double arg1);
    void on_z_SpinBox_valueChanged(double arg1);
    void on_scale_SpinBox_valueChanged(double arg1);
};
#endif // MAINWINDOW_H
