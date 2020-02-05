#include "polygon.h"
#include <iostream>

Polygon::Polygon(){

}

Polygon::Polygon(QVector<QPoint> points){
    this->polygonCoordinates = points;
}

QVector<QPoint> Polygon::getPolygonCoordinates(){
    return polygonCoordinates;
}

void Polygon::addPoint(int x, int y){
    QPoint point(x, y);
    polygonCoordinates.append(point);
}

void Polygon::setWidth(int wh){
    this->width = wh;
}

void Polygon::removeLastPoint(){
    polygonCoordinates.remove(polygonCoordinates.length() - 1);
}

int Polygon::getWidth(){
    return width;
}

void Polygon::clear(){
    polygonCoordinates.clear();
}

void Polygon::draw(QImage& image){
    if(polygonCoordinates.length() >= 1){
        for(int i = 0; i != polygonCoordinates.length() - 1; i++){
            drawLine(polygonCoordinates[i], polygonCoordinates[i + 1], image);
        }
        drawLine(polygonCoordinates[0], polygonCoordinates[polygonCoordinates.length() - 1], image);
    }
}

void Polygon::colorNeighbour(int x, int y, int dx, int dy, QImage& image){
    for(int i = 1; i < width + 1; i++){
        if(dx <= dy){
            image.setPixel(x + pow(-1, i), y, qRgb(0,0,0));
        }
        else if(dy < dx){
            image.setPixel(x, y - pow(-1, i), qRgb(0,0,0));
        }
    }
}

void Polygon::drawLine(QPoint start, QPoint end, QImage& image){
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
    colorNeighbour(x0, y0, diffx, diffy, image);
    image.setPixel(x0, y0, qRgb(0,0,0));

    while(x0 != x1 || y0 != y1)
    {
        image.setPixel(x0, y0,  qRgb(0,0,0));
        colorNeighbour(x0, y0, diffx, diffy, image);

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

Polygon::~Polygon(){}

void Polygon::writeToFile(QTextStream &stream){
    stream << "Polygon\n";
    for(QPoint point: polygonCoordinates)
        stream << point.x() << " " << point.y() << " " << width << '\n';
    stream << '\n';
}

IDraw* Polygon::readFromFile(QTextStream &stream){
    QString line;
    while(!stream.atEnd()){
        line = stream.readLine();
        if(line.isEmpty())
            break;
        polygonCoordinates.append(parseLine(line));
    }
    return this;
}

QPoint Polygon::parseLine(QString line){
    QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QPoint point(list[0].toInt(), list[1].toInt());
    width = list[2].toInt();
    return point;
}
