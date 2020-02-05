#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMouseTracking(true);
    //this->centralWidget()->setMouseTracking(true);

    setFixedSize(800, 600);
    leftWasPressed = false;
    deleteAllowed = false;

    scrollArea = new QScrollArea(this);
    label = new QLabel(this);
    label->setScaledContents(true);
    label->adjustSize();
    scrollArea->setWidget(label);
    scrollArea->move(0, 85);
    scrollArea->setFixedSize(800, 490);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setMouseTracking(true);
    label->setMouseTracking(true);
    label->adjustSize();

    image = new QImage(WIDTH, HEIGHT, QImage::Format_RGB32);
    tempImage = new QImage(WIDTH, HEIGHT, QImage::Format_RGB32);

    image->fill(qRgb(255, 255, 255));
    tempImage->fill(qRgb(255, 255, 255));

    //toDraw.readFile("/Users/kkania/Documents/Graphics/Tasks/Span/Files/trtr.le");
    drawAll();
    connect(&toDraw, SIGNAL(permanentUpdated()), this, SLOT(addPermanent()));
    connect(&toDraw, SIGNAL(tempUpdated()), this, SLOT(redraw()));
    connect(this, SIGNAL(upd()), this, SLOT(update()));
    connect(&toDraw, SIGNAL(redrawAll()), this, SLOT(redrawAll()));
}

void MainWindow::redraw(){
    emit upd();
}

void MainWindow::redrawAll(){
    image->fill(qRgb(255, 255, 255));
    for(IDraw* elem: toDraw.getSceneElements())
        elem->draw(*image);
    emit upd();
}

void MainWindow::addPermanent(){
    toDraw.getLastElem()->draw(*image);
    emit upd();
}

void MainWindow::paintEvent(QPaintEvent *event){
    drawScene();
    QPainter painter(this);
    label->setPixmap(QPixmap::fromImage(*tempImage));
    label->adjustSize();

    //label->setScaledContents(true);
    //painter.drawImage(0, 86, *tempImage);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(leftWasPressed){
        int y = scrollArea->verticalScrollBar()->value() + event->y() - 86;
        int x = scrollArea->horizontalScrollBar()->value() + event->x();
        if(ui->polygonButton->isChecked()){
            if(deleteAllowed)
                toDraw.removeLastPolygonPoint();
            toDraw.addTempPolygonPoint(x, y);
            deleteAllowed = true;
        }
        else if(ui->circleButton->isChecked()){
            toDraw.setTempCircleRadiusTo(x, y);
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(ui->circleButton->isChecked()){
        toDraw.saveTempCircle();
        leftWasPressed = false;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int y = scrollArea->verticalScrollBar()->value() + event->y() - 86;
    int x = scrollArea->horizontalScrollBar()->value() + event->x();
    if(event->button() == Qt::LeftButton){
        if(ui->circleButton->isChecked()){
            toDraw.addTempCircle(x, y, 1);
            leftWasPressed = true;
        }
        else if(ui->polygonButton->isChecked()){
            toDraw.addTempPolygonPoint(x, y);
            if(!leftWasPressed)
                toDraw.setTempPolygonWidth(ui->widthBox->currentIndex());
            leftWasPressed = true;
            deleteAllowed = false;
        }
        else if(ui->fill4Button->isChecked()){
            toDraw.setFill4(x, y, ui->colorBox->currentIndex());
        }
        else if(ui->fill8Button->isChecked()){
            toDraw.setFill8(x, y, ui->colorBox->currentIndex());
        }
    }
    else if((event->button() == Qt::RightButton) && leftWasPressed){
        if(ui->polygonButton->isChecked()){
            toDraw.removeLastPolygonPoint();
            toDraw.addTempPolygonPoint(x, y);
            toDraw.getTempPolygon().draw(*image);
            toDraw.saveTempPolygon();
            leftWasPressed = false;
            deleteAllowed = false;
        }
    }
}

void MainWindow::drawScene(){
    *tempImage = (image->copy());
    toDraw.getTempCircle().draw(*tempImage);
    toDraw.getTempPolygon().draw(*tempImage);
}

void MainWindow::drawAll(){
    for(IDraw* elem: toDraw.getSceneElements())
        elem->draw(*image);
}

MainWindow::~MainWindow()
{
    delete tempImage;
    delete image;
    delete ui;
}

void MainWindow::on_polygonButton_toggled(bool checked)
{
    if(checked){
        ui->polygonButton->setChecked(checked);
        ui->circleButton->setChecked(!checked);
        ui->fill4Button->setChecked(!checked);
        ui->fill8Button->setChecked(!checked);
    }
}

void MainWindow::on_circleButton_toggled(bool checked)
{
    if(checked){
        ui->circleButton->setChecked(checked);
        ui->polygonButton->setChecked(!checked);
        ui->fill4Button->setChecked(!checked);
        ui->fill8Button->setChecked(!checked);
    }
}

void MainWindow::on_fill8Button_toggled(bool checked)
{
    if(checked){
        ui->circleButton->setChecked(!checked);
        ui->polygonButton->setChecked(!checked);
        ui->fill4Button->setChecked(!checked);
        ui->fill8Button->setChecked(checked);
    }
}

void MainWindow::on_fill4Button_toggled(bool checked)
{
    if(checked){
        ui->circleButton->setChecked(!checked);
        ui->polygonButton->setChecked(!checked);
        ui->fill4Button->setChecked(checked);
        ui->fill8Button->setChecked(!checked);
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                            "/Users/kkania/Documents/Graphics/Tasks/Span/Files",
                                                            tr("*.spn"));
    if(!filename.isEmpty())
        toDraw.saveAs(filename);
}

void MainWindow::on_actionNew_file_2_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                            "/Users/kkania/Documents/Graphics/Tasks/Span/Files",
                                                            tr("*.spn"));
    if(!filename.isEmpty())
        toDraw.createNewProject(filename);
}

void MainWindow::on_actionOpen_file_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Save File"),
                                                            "/Users/kkania/Documents/Graphics/Tasks/Span/Files",
                                                            tr("*.spn"));
    if(!filename.isEmpty())
        toDraw.open(filename);
}

void MainWindow::on_actionSave_triggered()
{
    if(!toDraw.getCurrentFilename().isEmpty())
        toDraw.save();
    else{
        QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                                "/Users/kkania/Documents/Graphics/Tasks/Span/Files",
                                                                tr("*.spn"));
        if(!filename.isEmpty())
            toDraw.saveAs(filename);
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "This is programm can draw polygons,\
                                       circles and fill using 4 and 8 cohension");
}
