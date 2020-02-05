#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    image = new QImage(800, 600, QImage::Format_RGB32);
    image->fill(Qt::white);
    spSetupWindow = new SplineSetup(this);
    //globalScene.addSpline(spline);
    globalScene.draw(*image);
    connect(spSetupWindow, SIGNAL(splineReady()), this, SLOT(addSpline()));
    connect(&globalScene, SIGNAL(redraw()), this, SLOT(update()));
    wasPressed = false;
    x_prev = -1;
    y_prev = -1;
    globalScene.readFile("/Users/kkania/Documents/Graphics/Tasks/WF/Files/test.wf", *image);
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
}

MainWindow::~MainWindow(){
    delete image;
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(!wasPressed)
        return;
    double angle_x, angle_y, angle_z;

    angle_x = ((double)event->y() - y_prev) / 100.;
    angle_z = ((double)event->x() - x_prev) / 100.;
    angle_y = angle_x * angle_z;

    x_prev = (double)event->x();
    y_prev = (double)event->y();

    globalScene.rotate(*image, angle_x, angle_y, angle_z);

}

void MainWindow::mousePressEvent(QMouseEvent *event){
    wasPressed = true;
    x_prev = event->x();
    y_prev = event->y();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    wasPressed = false;
    x_prev = -1;
    y_prev = -1;
}

void MainWindow::addSpline(){
    globalScene.addSpline(Spline(spSetupWindow->getPoints()), spSetupWindow->getScale(), spSetupWindow->getMove());
    spSetupWindow->clear();
    globalScene.draw(*image);
}

void MainWindow::on_spline_setup_clicked(){
    spSetupWindow->show();
}

void MainWindow::on_zn_SpinBox_valueChanged(double arg1){
    globalScene.setZn(arg1, *image);
}

void MainWindow::on_zf_SpinBox_valueChanged(double arg1){
    globalScene.setZf(arg1, *image);
}

void MainWindow::on_sw_SpinBox_valueChanged(double arg1){
    globalScene.setSw(arg1, *image);
}

void MainWindow::on_sh_SpinBox_valueChanged(double arg1){
    globalScene.setSh(arg1, *image);
}

void MainWindow::on_n_spinBox_valueChanged(int arg1){
    globalScene.setN(arg1, *image);
}

void MainWindow::on_k_spinBox_valueChanged(int arg1){
    globalScene.setK(arg1, *image);
}

void MainWindow::on_x_SpinBox_valueChanged(double arg1){
    globalScene.changePos(ui->obj_spinBox->value(), ui->x_SpinBox->value() / 10., ui->y_SpinBox->value() / 10., ui->z_SpinBox->value() / 10., *image);
}

void MainWindow::on_y_SpinBox_valueChanged(double arg1){
    globalScene.changePos(ui->obj_spinBox->value(), ui->x_SpinBox->value() / 10., ui->y_SpinBox->value() / 10., ui->z_SpinBox->value() / 10., *image);
}

void MainWindow::on_z_SpinBox_valueChanged(double arg1){
    globalScene.changePos(ui->obj_spinBox->value(), ui->x_SpinBox->value() / 10., ui->y_SpinBox->value() / 10., ui->z_SpinBox->value() / 10., *image);
}

void MainWindow::on_scale_SpinBox_valueChanged(double arg1){
    globalScene.changeScale(ui->obj_spinBox->value(), ui->scale_SpinBox->value(), *image);
}
