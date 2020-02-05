#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define WIDTH 2000
#define HEIGHT 2000

#include <QMainWindow>
#include <QMainWindow>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QImage>
#include <QScrollArea>
#include <QLabel>
#include <QGridLayout>
#include <QScrollBar>

#include "scene.h"
#include "circle.h"
#include "polygon.h"
#include "idraw.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QImage *tempImage;
    QImage *image;
    Scene toDraw;
    QScrollArea *scrollArea;
    QLabel *label;
    //QGridLayout *layout;

    bool leftWasPressed;
    bool deleteAllowed;

public:
    MainWindow(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void drawScene();

    void drawAll();

    ~MainWindow();

Q_SIGNALS:
    void upd();

public slots:
    void redraw();

    void addPermanent();

    void redrawAll();

private slots:
    void on_polygonButton_toggled(bool checked);

    void on_circleButton_toggled(bool checked);

    void on_fill8Button_toggled(bool checked);

    void on_fill4Button_toggled(bool checked);

    void on_actionSave_as_triggered();

    void on_actionNew_file_2_triggered();

    void on_actionOpen_file_triggered();

    void on_actionSave_triggered();

    void on_actionAbout_triggered();
};
#endif // MAINWINDOW_H
