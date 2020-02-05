#include "matrixsetup.h"
#include "ui_matrixsetup.h"

matrixSetup::matrixSetup(QWidget *parent): QDialog(parent), ui(new Ui::matrixSetup){
    ui->setupUi(this);
    autoDiv = false;
    matrix.resize(3);
    for(int i = 0; i != 3; i++)
        matrix[i].resize(3);
}

matrixSetup::~matrixSetup(){
    delete ui;
}

void matrixSetup::on_buttonBox_accepted(){
    matrix[0][0] = ui->a00->value();
    matrix[0][1] = ui->a01->value();
    matrix[0][2] = ui->a02->value();
    matrix[1][0] = ui->a10->value();
    matrix[1][1] = ui->a11->value();
    matrix[1][2] = ui->a12->value();
    matrix[2][0] = ui->a20->value();
    matrix[2][1] = ui->a21->value();
    matrix[2][2] = ui->a22->value();

    div = ui->div->value();
    shift = ui->shift->value();
    autoDiv = ui->autoDiv->isChecked();
    emit matrixUpdated();
}

QVector<QVector<int>> matrixSetup::getMatrix(){
    return matrix;
}

int matrixSetup::getDiv(){
    return div;
}

int matrixSetup::getShift(){
    return shift;
}

bool matrixSetup::getAutoDiv(){
    return autoDiv;
}
