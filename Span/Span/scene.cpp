#include "scene.h"

Scene::Scene(){
    currentFile = "";

}

QVector<IDraw*>& Scene::getSceneElements(){
    return sceneElements;
}

IDraw* Scene::getLastElem(){
    return sceneElements.last();
}

void Scene::addTempPolygonPoint(int x, int y){
    //fixBorders(x, y);
    tempPolygon.addPoint(x, y);
    emit tempUpdated();
}

void Scene::addTempCircle(int x, int y, int radius){
    tempCircle.setCenter(x, y);
    tempCircle.setRadius(radius);
    emit tempUpdated();
}

void Scene::saveTempCircle(){
    sceneElements.append(new Circle(tempCircle));
    tempCircle.clear();
    emit permanentUpdated();
}

void Scene::saveTempPolygon(){
    sceneElements.append(new Polygon(tempPolygon));
    tempPolygon.clear();
    emit permanentUpdated();
}

void Scene::setTempCircleRadiusTo(int x, int y){
//    //fixBorders(x, y);
    int rad = static_cast<int>(sqrt(pow(x - tempCircle.getCenter().x(), 2) + pow(y - tempCircle.getCenter().y(), 2)));
//    if(tempCircle.getCenter().x() + rad > WIDTH) rad = WIDTH - tempCircle.getCenter().x();
//    if(tempCircle.getCenter().x() - rad < 0) rad = tempCircle.getCenter().x();
//    if(tempCircle.getCenter().y() + rad > HEIGHT) rad = HEIGHT - tempCircle.getCenter().y();
//    if(tempCircle.getCenter().y() - rad > WIDTH) rad = tempCircle.getCenter().y();
    tempCircle.setRadius(rad);
    emit tempUpdated();
}

void Scene::removeLastPolygonPoint(){
    tempPolygon.removeLastPoint();
    emit tempUpdated();
}

Circle Scene::getTempCircle(){
    return tempCircle;
}

Polygon Scene::getTempPolygon(){
    return tempPolygon;
}

void Scene::setFill4(int x, int y, int color){
    //fixBorders(x, y);
    sceneElements.append(new Fill(x, y, color, 4));
    emit permanentUpdated();
}

void Scene::setFill8(int x, int y, int color){
    //fixBorders(x, y);
    sceneElements.append(new Fill(x, y, color, 8));
    emit permanentUpdated();
}

void Scene::setTempPolygonWidth(int width){
    tempPolygon.setWidth(width);
}

void Scene::fixBorders(int& x, int& y){
    if(x < 0) x = 0;
    if(y < 0) y = 0;
    if(x > WIDTH) x = WIDTH;
    if(y > HEIGHT) y = HEIGHT;
}

void Scene::resetScene(){
    sceneElements.clear();
    tempCircle.setRadius(-1);
    tempPolygon.clear();
    emit redrawAll();
}

bool Scene::readFile(QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite))
        return false;
    QTextStream stream(&file);
    QString line;
    while(!stream.atEnd()){
        line = stream.readLine();
        if(line == "Polygon")
            sceneElements.append((new Polygon())->readFromFile(stream));
        else if(line == "Circle")
            sceneElements.append((new Circle())->readFromFile(stream));
        else if(line == "Fill")
            sceneElements.append((new Fill())->readFromFile(stream));
    }

    file.close();
    return true;
}

bool Scene::createNewProject(QString filename){
    resetScene();
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite))
        return false;
    file.close();
    currentFile = filename;
    return true;
}

bool Scene::save(){
    QFile file(currentFile);
    if(!file.open(QIODevice::ReadWrite))
        return false;
    file.resize(0);
    QTextStream stream(&file);
    for(int i = 0; i != sceneElements.length(); i++){
        sceneElements[i]->writeToFile(stream);
        stream << '\n';
    }
    file.close();

    return true;
}

bool Scene::saveAs(QString filename){
    QFile file(filename);

    if(!file.open(QIODevice::ReadWrite))
        return false;
    file.resize(0);
    QTextStream stream(&file);
    for(int i = 0; i != sceneElements.length(); i++)
        sceneElements[i]->writeToFile(stream);
    file.close();
    currentFile = filename;

    return true;
}

bool Scene::open(QString filename){
    resetScene();
    readFile(filename);
    currentFile = filename;
    emit redrawAll();
    return true;
}

QString Scene::getCurrentFilename(){
    return currentFile;
}

Scene::~Scene(){}
