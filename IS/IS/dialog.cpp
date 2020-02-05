#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent): QDialog(parent), ui(new Ui::Dialog){
    ui->setupUi(this);
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    minY = ui->minY->value();
    minX = ui->minX->value();
    maxY = ui->maxY->value();
    maxX = ui->maxX->value();
    net_k = ui->net_k->value();
    net_m = ui->net_m->value();
    emit updatedParams();
}

double Dialog::getMaxX(){
    return maxX;
}

double Dialog::getMaxY(){
    return maxY;
}

double Dialog::getMinX(){
    return minX;
}

double Dialog::getMinY(){
    return minY;
}

double Dialog::getNet_k(){
    return net_k;
}

double Dialog::getNet_m(){
    return net_m;
}
