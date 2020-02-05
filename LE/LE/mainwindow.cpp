#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), timer(this){

    ui->setupUi(this);
    leftWasPressed = false;
    deleteAllowed = false;

    image = new QImage(1440, 900, QImage::Format_RGB32);

    this->setMouseTracking(true);
    this->centralWidget()->setMouseTracking(true);
    toDraw.readFile("/Users/kkania/Documents/Graphics/Tasks/LE/LE/files/ttt.le");
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(50);
}

void MainWindow::paintEvent(QPaintEvent *event){
    drawScene();
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(leftWasPressed){
        if(deleteAllowed)
            toDraw.removeLastTempCoordinates();
        toDraw.addTempCoordinates(event->x(), event->y());
        deleteAllowed = true;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        toDraw.addTempCoordinates(event->x(), event->y());
        leftWasPressed = true;
        deleteAllowed = false;
    }
    else if((event->button() == Qt::RightButton) && leftWasPressed){
        toDraw.addTempCoordinates(event->x(), event->y());
        toDraw.saveTempPolyline();
        leftWasPressed = false;
        deleteAllowed = false;
    }
}

void MainWindow::drawLine(QPoint start, QPoint end){
    int x0 = start.x();
    int y0 = start.y();
    int x1 = end.x();
    int y1 = end.y();

    int diffx = abs(x1 - x0);
    int diffy = abs(y1 - y0);
    int dx = -1;
    int dy = -1;

    if(x0 < x1)
        dx = 1;
    if(y0 < y1)
        dy = 1;

    int error = diffx - diffy;
    image->setPixel(x0, y0, qRgb(0,0,0));

    while(x0 != x1 || y0 != y1)
    {
        image->setPixel(x0, y0,  qRgb(0,0,0));

        int error2 = error * 2;

        if(error2 > -diffy){
            error -= diffy;
            x0 += dx;
        }

        if(error2 < diffx){
            error += diffx;
            y0 += dy;
        }
    }
}






void MainWindow::drawScene(){
    image->fill(qRgb(255, 255, 255));

    QVector<QPoint> tmpCoord = toDraw.getTempPolyline().getPolylineCoordinates();
    if(tmpCoord.length() > 0){
        for(int i = 0; i != tmpCoord.length() - 1; i++){
            drawLine(tmpCoord[i], tmpCoord[i + 1]);
        }
    }

    QVector<Polyline> scene = toDraw.getScene();
    for(Polyline line: scene){
        QVector<QPoint> coord = line.getPolylineCoordinates();
        for(int i = 0; i != coord.length() - 1; i++){
            drawLine(coord[i], coord[i + 1]);
        }
    }
}

MainWindow::~MainWindow(){
    delete image;
    delete ui;
}


void MainWindow::on_actionNew_file_triggered(){
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "/Users/kkania/Documents/Graphics/Tasks/LE/LE/files",
                                                    tr("*.le"));
    if(!filename.isEmpty())
        toDraw.createNewProject(filename);
}

void MainWindow::on_actionSave_triggered(){
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "/Users/kkania/Documents/Graphics/Tasks/LE/LE/files",
                                                    tr("*.le"));
    if(!filename.isEmpty())
        toDraw.saveAs(filename);
}

void MainWindow::on_actionOpen_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Open"),
                                                    "/Users/kkania/Documents/Graphics/Tasks/LE/LE/files",
                                                    "*.le");
    if(!filename.isEmpty())
        toDraw.open(filename);
}

void MainWindow::on_actionSave_2_triggered(){
    if(toDraw.isEmptyFile()){
        QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "/Users/kkania/Documents/Graphics/Tasks/LE/LE/files",
                                                        tr("*.le"));
        if(!filename.isEmpty())
            toDraw.saveAs(filename);
    }
    else
        toDraw.save();
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "This is programm can draw polylines");
}

void MainWindow::on_actionDelete_last_polyline_triggered()
{
    toDraw.removeLastPolyline();
}
