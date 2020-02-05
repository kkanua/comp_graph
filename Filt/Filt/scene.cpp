#include "scene.h"
#include <iostream>

Scene::Scene(){

}

Scene::Scene(QImage* src, QImage* dst){
    sourceImage = src;
    destImage = dst;
}

void Scene::toBW(){
    editor.toBW(*sourceImage, *destImage);
    emit sceneUpd();
}

void Scene::negative(){
    editor.negative(*sourceImage, *destImage);
    emit sceneUpd();
}

void Scene::blur(){
    QVector<QVector<int>> matrix = {{0, 1, 0},
                                    {1, 2, 1},
                                    {0, 1, 0}};
    editor.matrixTransform(matrix, 6, 0, false, *sourceImage, *destImage);
    emit sceneUpd();
}

void Scene::sharp(){
    QVector<QVector<int>> matrix = {{0, -1, 0},
                                       {-1, 5, -1},
                                       {0, -1, 0}};

    editor.matrixTransform(matrix, 1, 0, false, *sourceImage, *destImage);
    emit sceneUpd();
}

void Scene::embossing(){
    QVector<QVector<int>> matrix = {{0, -1, 0},
                                       {1, 0, -1},
                                       {0, 1, 0}};
    editor.matrixTransform(matrix, 1, 128, false, *sourceImage, *destImage);
    emit sceneUpd();
}

void Scene::pathSelection(int shift){    //add threshold
    QVector<QVector<int>> matrix = {{0, -1, 0},
                                       {-1, 4, -1},
                                       {0, -1, 0}};
    editor.matrixTransform(matrix, 1, shift, false, *sourceImage, *destImage);

    emit sceneUpd();
}

void Scene::gammaCorrection(double gamma){
    editor.gammaCorrection(*sourceImage, *destImage, gamma);
    emit sceneUpd();
}

void Scene::aquarell(){
    QImage temp = *sourceImage;
    QVector<QVector<int>> matrix = {{0, -1, 0},
                                       {-1, 5, -1},
                                       {0, -1, 0}};

    editor.medianFilt(*sourceImage, *destImage);
    copyDstToSrc();
    editor.matrixTransform(matrix, 1, 0, false, *sourceImage, *destImage);
    *sourceImage = temp;
    emit sceneUpd();
}

void Scene::identTransform(){
    QVector<QVector<int>> matrix = {{0, 0, 0},
                                    {0, 1, 0},
                                    {0, 0, 0}};
    editor.matrixTransform(matrix, 1, 0, false, *sourceImage, *destImage);
    emit sceneUpd();
}

void Scene::customMatrixFilt(QVector<QVector<int>> matrix, int div, int shift, bool autoDiv){
    editor.matrixTransform(matrix, div, shift, autoDiv, *sourceImage, *destImage);
    emit sceneUpd();
}

void Scene::openImage(QString filename){
    sourceImage->load(filename);
    *destImage = QImage(sourceImage->width(), sourceImage->height(), QImage::Format_RGB32);
    destImage->fill(qRgb(0, 0, 255));
    emit sceneUpd();
}

void Scene::copyDstToSrc(){
    *sourceImage = destImage->copy();
    emit sceneUpd();
}

void Scene::copySrcToDst(){
    *destImage = sourceImage->copy();
    emit sceneUpd();
}

bool Scene::saveImageDst(QString filename){
    filename += ".png";
    return destImage->save(filename, "PNG");
}

void Scene::pixel(){
    editor.pixel(*sourceImage, *destImage);
    emit sceneUpd();
}
