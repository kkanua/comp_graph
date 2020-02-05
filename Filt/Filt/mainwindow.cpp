#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    backgroundSrcImg = new QImage(this->width() / 2 - 10, this->height() - 100, QImage::Format_RGB32);
    backgroundDstImg = new QImage(this->width() / 2 - 10, this->height() - 100, QImage::Format_RGB32);
    srcImg = new QImage("/Users/kkania/Documents/Graphics/Tasks/Filt/Files/IMG_7407.JPG");
    dstImg = new QImage("/Users/kkania/Documents/Graphics/Tasks/Filt/Files/IMG_7407.JPG");
    backgroundSrcImg->fill(qRgb(255, 255, 255));
    backgroundDstImg->fill(qRgb(255, 255, 255));
    scene = new Scene(srcImg, dstImg);

    matrixWindow = new matrixSetup(this);
    counter = 0;
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);

    connect(scene, SIGNAL(sceneUpd()), this, SLOT(update()));
    connect(matrixWindow, SIGNAL(matrixUpdated()), this, SLOT(matrixFilt()));
}


void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainter pt1(backgroundSrcImg);
    QPainter pt2(backgroundDstImg);

    pt1.drawImage(backgroundSrcImg->width() / 2 - srcImg->width() / 2, backgroundSrcImg->height() / 2 - srcImg->height() / 2, *srcImg);
    pt2.drawImage(backgroundDstImg->width() / 2 - dstImg->width() / 2, backgroundDstImg->height() / 2 - dstImg->height() / 2, *dstImg);

    painter.drawImage(5, 60, *backgroundSrcImg);
    painter.drawImage(5 + backgroundSrcImg->width() + 5, 60, *backgroundDstImg);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    *backgroundSrcImg = QImage(this->width() / 2 - 10, this->height() - 100, QImage::Format_RGB32);
    *backgroundDstImg = QImage(this->width() / 2 - 10, this->height() - 100, QImage::Format_RGB32);
    backgroundSrcImg->fill(qRgb(255, 255, 255));
    backgroundDstImg->fill(qRgb(255, 255, 255));
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_actionOpen_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Save File"),
                                                                "/Users/kkania/Documents/Graphics/Tasks/Filt/Files",
                                                                tr("*.bmp *.png *.gif *.jpg"));
    scene->openImage(filename);
    backgroundSrcImg->fill(qRgb(255, 255, 255));
    backgroundDstImg->fill(qRgb(255, 255, 255));
}

void MainWindow::on_actionSave_triggered(){
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                                "/Users/kkania/Documents/Graphics/Tasks/Filt/Files",
                                                                tr(""));
    scene->saveImageDst(filename);

}

void MainWindow::matrixFilt(){
    scene->customMatrixFilt(matrixWindow->getMatrix(), matrixWindow->getDiv(), matrixWindow->getShift(), matrixWindow->getAutoDiv());
}


void MainWindow::on_actionMove_dst_to_src_triggered(){
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    scene->copyDstToSrc();
}

void MainWindow::on_actionCopy_src_to_dst_triggered(){
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    scene->copySrcToDst();
}

void MainWindow::on_blackWhite_clicked(){
    std::cout << QTime::currentTime().toString("hh:mm").toStdString() << "-" << QDate::currentDate().toString("dd_MM_yyyy").toStdString() << std::endl;
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    scene->toBW();
}

void MainWindow::on_negative_clicked(){
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    scene->negative();
}

void MainWindow::on_sharp_clicked(){
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    scene->sharp();
}

void MainWindow::on_blur_clicked(){
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    scene->blur();
    //scene->pixel();
}

void MainWindow::on_aquarel_clicked(){
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    scene->aquarell();
}

void MainWindow::on_emboss_clicked(){
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    scene->embossing();
}

void MainWindow::on_pthSelection_clicked(){
    ui->sliderPSelect->setEnabled(true);
    ui->doubleSpinBox->setEnabled(false);
    scene->pathSelection(ui->sliderPSelect->value());
}

void MainWindow::on_sliderPSelect_valueChanged(int value){
    scene->pathSelection(value);
}

void MainWindow::on_gamma_clicked(){
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(true);
    scene->gammaCorrection(0.1);
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1){
    scene->gammaCorrection(arg1);
    QPixmap originalPixmap = QWidget::grab(this->rect());
    originalPixmap.save("/Users/kkania/Desktop/file" + QString::number(counter), "PNG");
    counter++;
}

void MainWindow::on_ident_clicked(){
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    scene->identTransform();
}

void MainWindow::on_custom_clicked(){
    ui->sliderPSelect->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    matrixWindow->show();
}
