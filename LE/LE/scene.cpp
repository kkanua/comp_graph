#include "scene.h"

Scene::Scene(){currentFile = "";}

void Scene::addTempCoordinates(int x, int y){
    tempPolyline.addCoordinates(x, y);
}

void Scene::addTempCoordinates(QPoint point){
    tempPolyline.addCorrdinates(point);
}

void Scene::resetTempPolyline(){
    tempPolyline.removeLine();
}

void Scene::saveTempPolyline(){
    scenePL.append(tempPolyline);
    tempPolyline.removeLine();
}

Polyline Scene::getTempPolyline(){
    return tempPolyline;
}

void Scene::removeLastTempCoordinates(){
    tempPolyline.removeLastPoint();
}

QVector<Polyline>& Scene::getScene(){
    return scenePL;
}

QPoint Scene::getCoordinatesFromStr(QString &str){
    QStringList list = str.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QPoint point(list[0].toInt(), list[1].toInt());
    return point;
}

void Scene::removeLastPolyline(){
    if(scenePL.length() > 0)
        scenePL.remove(scenePL.length() - 1);
}

void Scene::resetScene(){
    scenePL.clear();
    tempPolyline.removeLine();
}


bool Scene::readFile(QString filename){
    currentFile = filename;
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream(&file);
    QString line;
    int amount = file.readLine().toInt();
    file.readLine();

    while(!stream.atEnd()){
        line = stream.readLine();
        if(line == "Polyline"){
            while(!stream.atEnd()){
                line = stream.readLine();
                if(line.isEmpty()){
                    saveTempPolyline();
                    break;
                }
                addTempCoordinates(getCoordinatesFromStr(line));
            }
        }
    }
    saveTempPolyline();
    file.close();
    return true;
}

bool Scene::createNewProject(QString filename){
    currentFile = filename;
    resetScene();
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    file.close();
    return true;
}

bool Scene::isEmptyFile(){
    return currentFile.isEmpty();
}

bool Scene::save(){
    QFile file(currentFile);

    if(!file.open(QIODevice::ReadWrite))
        return false;
    file.resize(0);
    QTextStream stream(&file);

    stream << scenePL.length() << "\n";
    for(Polyline line: scenePL){
        stream << "\n";
        stream << "Polyline\n";
        for(QPoint point: line.getPolylineCoordinates()){
            stream << point.x() << " " << point.y() << "\n";
        }
    }
    file.close();

    return true;
}

bool Scene::saveAs(QString filename){
    currentFile = filename;
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite))
        return false;

    QTextStream stream(&file);

    stream << scenePL.length() << "\n";
    for(Polyline line: scenePL){
        stream << "\n";
        stream << "Polyline\n";
        for(QPoint point: line.getPolylineCoordinates()){
            stream << point.x() << " " << point.y() << "\n";
        }
    }
    file.close();

    return true;
}

void Scene::open(QString filename){
    resetScene();
    readFile(filename);
}
