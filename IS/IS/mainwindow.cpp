#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setMouseTracking(true);
    this->centralWidget()->setMouseTracking(true);
    //this->setFixedSize(IMAGE_WIDTH + 300, IMAGE_HEIGHT + 300);

    imageColorMap = new QImage(IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_RGB32);
    imageLegend = new QImage(30, IMAGE_HEIGHT, QImage::Format_RGB32);
    imageIsolinesMap = new QImage(IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_ARGB32);
    imageIsolinesLeg = new QImage(30, IMAGE_HEIGHT, QImage::Format_ARGB32);
    imageMapVals = new QImage(20, IMAGE_HEIGHT, QImage::Format_ARGB32);
    imageLegVals = new QImage(20, IMAGE_HEIGHT, QImage::Format_ARGB32);

    imageIsolinesLeg->fill(qRgba(0, 0, 0, 0));
    imageIsolinesMap->fill(qRgba(0, 0, 0, 0));

    imageLegVals->fill(qRgba(0, 0, 0, 0));
    imageMapVals->fill(qRgba(0, 0, 0, 0));

    scene.readFile("/Users/kkania/Documents/Graphics/Tasks/IS/Files/setup.is");

    scene.drawLegend(*imageLegend, *imageLegVals);
    scene.drawColorMap(*imageColorMap, *imageMapVals);
    isIsolines = false;
    isGrid = false;
    wasPressed = false;
    isDithering = false;
    isInterpolated = false;

    window = new Dialog(this);

    connect(window, SIGNAL(updatedParams()), this, SLOT(setParams()));
    connect(this, SIGNAL(upd()), this, SLOT(update()));

}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    setImageBorders();

    painter.drawImage(15, 30, *imageMapVals);
    painter.drawImage(imageColorMap->width() + 60, 30, *imageLegVals);
    painter.drawImage(40, 30, *imageColorMap);
    painter.drawImage(40, 30, *imageIsolinesMap);
    painter.drawImage(imageColorMap->width() + 90, 30, *imageLegend);
    painter.drawImage(imageColorMap->width() + 90, 30, *imageIsolinesLeg);

}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    double x = scene.getX(event->x() - 40, *imageColorMap);
    double y = scene.getY(event->y() - 30, *imageColorMap);
    double fVal = scene.getFvalue(x, y);
    if(!((event->x() > 40 && event->y() > 30) && (event->x() - 40 <= imageColorMap->width() && event->y() - 30 <= imageColorMap->height())))
        return;

    ui->statusbar->showMessage("x: " + QString::number(x) + " y: " + QString::number(y) + " | f(x, y)= " + QString::number(fVal));

    if(!wasPressed)
        return;
    imageIsolinesLeg->fill(qRgba(0, 0, 0, 0));
    imageIsolinesMap->fill(qRgba(0, 0, 0, 0));
    if(isIsolines){
        scene.drawIsolinesLeg(*imageIsolinesLeg);
        scene.drawIsolinesMap(*imageIsolinesMap);
    }
    if(isGrid)
        scene.drawGrid(*imageIsolinesMap);
    scene.drawIsoline(*imageIsolinesMap, fVal);
    emit upd();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    imageIsolinesLeg->fill(qRgba(0, 0, 0, 0));
    imageIsolinesMap->fill(qRgba(0, 0, 0, 0));
    if(isIsolines){
        scene.drawIsolinesLeg(*imageIsolinesLeg);
        scene.drawIsolinesMap(*imageIsolinesMap);
    }
    if(isGrid)
        scene.drawGrid(*imageIsolinesMap);
    double x = scene.getX(event->x() - 40, *imageColorMap);
    double y = scene.getY(event->y() - 30, *imageColorMap);
    scene.drawIsoline(*imageIsolinesMap, scene.getFvalue(x, y));
    wasPressed = true;
    emit upd();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    wasPressed = false;
}

void MainWindow::setImageBorders(){
    QPainter p1(imageColorMap);
    QPainter p2(imageLegend);
    p1.setPen(Qt::white);
    p2.setPen(Qt::white);

    p1.drawLine(0, 0, imageColorMap->width() - 1, 0);
    p1.drawLine(0, 0, 0, imageColorMap->height() - 1);

    p1.drawLine(imageColorMap->width() - 1, 0, imageColorMap->width() - 1, imageColorMap->height() - 1);
    p1.drawLine(0, imageColorMap->height() - 1, imageColorMap->width() - 1, imageColorMap->height() - 1);

    p2.drawLine(0, 0, imageLegend->width() - 1, 0);
    p2.drawLine(0, 0, 0, imageLegend->height() - 1);

    p2.drawLine(imageLegend->width() - 1, 0, imageLegend->width() - 1, imageLegend->height() - 1);
    p2.drawLine(0, imageLegend->height() - 1, imageLegend->width() - 1, imageLegend->height() - 1);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    delete imageColorMap;
    delete imageLegend;
    delete imageIsolinesMap;
    delete imageIsolinesLeg;
    delete imageLegVals;
    delete imageMapVals;

    imageColorMap = new QImage(this->width() - 150, this->height() - 70, QImage::Format_RGB32);
    imageLegend = new QImage(30, this->height() - 70, QImage::Format_RGB32);
    imageIsolinesMap = new QImage(this->width() - 150, this->height() - 70, QImage::Format_ARGB32);
    imageIsolinesLeg = new QImage(30, this->height() - 70, QImage::Format_ARGB32);
    imageMapVals = new QImage(30, this->height() - 70, QImage::Format_ARGB32);
    imageLegVals = new QImage(30, this->height() - 70, QImage::Format_ARGB32);

    imageIsolinesLeg->fill(qRgba(0, 0, 0, 0));
    imageIsolinesMap->fill(qRgba(0, 0, 0, 0));
    imageLegVals->fill(qRgba(0, 0, 0, 0));
    imageMapVals->fill(qRgba(0, 0, 0, 0));

    scene.drawLegend(*imageLegend, *imageLegVals);
    scene.drawColorMap(*imageColorMap, *imageMapVals);

    if(isDithering){
        scene.drawDitheringLeg(*imageLegend);
        scene.drawDitheringMap(*imageColorMap);
    }

    if(isInterpolated){
        scene.drawInterpolationLeg(*imageLegend);
        scene.drawInterpolationMap(*imageColorMap);
    }
    if(isIsolines){
        scene.drawIsolinesLeg(*imageIsolinesLeg);
        scene.drawIsolinesMap(*imageIsolinesMap);
    }
    if(isGrid)
        scene.drawGrid(*imageIsolinesMap);

    emit upd();
}

MainWindow::~MainWindow(){
    delete ui;
    delete imageColorMap;
    delete imageLegend;
    delete imageIsolinesMap;
    delete imageIsolinesLeg;
}

void MainWindow::setParams(){
    QVector<double> parametrs;
    parametrs.append(window->getMaxX());
    parametrs.append(window->getMaxY());
    parametrs.append(window->getMinX());
    parametrs.append(window->getMinY());
    parametrs.append(window->getNet_k());
    parametrs.append(window->getNet_m());
    scene.updateParametrs(parametrs);
    imageIsolinesLeg->fill(qRgba(0, 0, 0, 0));
    imageIsolinesMap->fill(qRgba(0, 0, 0, 0));
    imageLegVals->fill(qRgba(0, 0, 0, 0));
    imageMapVals->fill(qRgba(0, 0, 0, 0));
    scene.recalculateMap(*imageColorMap, *imageMapVals);
    scene.recalculateLeg(*imageLegend, *imageLegVals);
    isGrid = false;
    isIsolines = false;
    emit upd();
}

void MainWindow::on_pushButton_clicked(){
    window->show();
}

void MainWindow::on_interpolation_clicked(bool checked)
{
    if(!isInterpolated){
        scene.drawInterpolationLeg(*imageLegend);
        scene.drawInterpolationMap(*imageColorMap);
        isInterpolated = true;
        isDithering = false;
    }
    emit upd();
}

void MainWindow::on_dither_clicked(bool checked)
{
    if(!isDithering){
        scene.drawDitheringLeg(*imageLegend);
        scene.drawDitheringMap(*imageColorMap);
        isDithering = true;
        isInterpolated = false;
    }
    emit upd();
}

void MainWindow::on_isolines_clicked()
{
    if(isIsolines){
        imageIsolinesLeg->fill(qRgba(0, 0, 0, 0));
        imageIsolinesMap->fill(qRgba(0, 0, 0, 0));
        if(isGrid)
            scene.drawGrid(*imageIsolinesMap);

        isIsolines = false;
    }
    else{
        scene.drawIsolinesLeg(*imageIsolinesLeg);
        scene.drawIsolinesMap(*imageIsolinesMap);
        isIsolines = true;
    }
    emit upd();
}

void MainWindow::on_grid_clicked()
{
    if(isGrid){
        imageIsolinesMap->fill(qRgba(0, 0, 0, 0));
        if(isIsolines){
            scene.drawIsolinesLeg(*imageIsolinesLeg);
            scene.drawIsolinesMap(*imageIsolinesMap);
        }
        isGrid = false;
    }
    else{
        scene.drawGrid(*imageIsolinesMap);
        isGrid = true;
    }
    emit upd();
}

void MainWindow::on_map_clicked()
{
    scene.drawColorMap(*imageColorMap, *imageMapVals);
    scene.drawLegend(*imageLegend, *imageLegVals);
    isDithering = false;
    isInterpolated = false;
    emit upd();
}
