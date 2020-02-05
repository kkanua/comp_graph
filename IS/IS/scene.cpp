#include "scene.h"

Scene::Scene(){

}

void Scene::drawLegend(QImage &image, QImage& imageVals){
    map.draw(image, imageVals, &f.leg);
}

void Scene::drawColorMap(QImage &image, QImage& imageVals){
    map.draw(image, imageVals, &f.f);
}

void Scene::drawDitheringMap(QImage &image){
    map.drawInterpolation(image, true, &f.f);
}

void Scene::drawInterpolationMap(QImage &image){
    map.drawInterpolation(image, false, &f.f);
}

void Scene::drawInterpolationLeg(QImage &image){
     map.drawInterpolation(image, false, &f.leg);
}

void Scene::drawDitheringLeg(QImage &image){
    map.drawInterpolation(image, true, &f.leg);
}

void Scene::updateParametrs(QVector<double> params){
    map.setParams(params);
}

void Scene::recalculateMap(QImage &image, QImage& imageVals){
    map.recalculate(image, imageVals, &f.f);
}

void Scene::recalculateLeg(QImage &image, QImage& imageVals){
    map.recalculate(image, imageVals, &f.leg);
}

void Scene::drawIsolinesMap(QImage &image){
    map.drawIsoline(image, map.getIsolineLevels(image, &f.f), &f.f);
}

void Scene::drawIsolinesLeg(QImage &image){
    map.drawIsoline(image, map.getIsolineLevels(image, &f.leg), &f.leg);
}

double Scene::getX(int u, QImage& image){
    return map.x(u, image);
}

double Scene::getY(int v, QImage& image){
    return map.y(v, image);
}

double Scene::getFvalue(double x, double y){
    return f.f(x, y);
}

void Scene::drawGrid(QImage& image){
    map.drawGrid(image);
}

void Scene::drawIsoline(QImage &image, double isoline){
    QVector<double> is;
    is.append(isoline);
    map.drawIsoline(image, is, &f.f);
}

void Scene::readFile(QString filename){
    QFile file(filename);
    QVector<QColor> colors;
    QVector<double> list;
    //QString r, g, b;
    if(!file.open(QIODevice::ReadWrite))
        return ;
    QTextStream stream(&file);
    QString line;
    line += stream.readLine();
    line += " ";
    line += stream.readLine();
    line += " ";
    line += stream.readLine();
    line += " ";
    line += stream.readLine();
    map.setParams(parseArgs(line));
    line = stream.readLine();
    map.setNumberOfLevels(line.toInt());

    while(!stream.atEnd()){
        line = stream.readLine();
        list = parseArgs(line);
        colors.append(QColor(list[0], list[1], list[2]));
    }

    map.setIsoColor(colors.last());
    colors.remove(colors.length() - 1);
    map.setColors(colors);

    file.close();
}

QVector<double> Scene::parseArgs(QString line){
    QVector<double> vals;
    QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    for(QString str: list)
        vals.append(str.toDouble());
    return vals;
}
