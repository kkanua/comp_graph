#include "circle.h"

Circle::Circle(){
    radius = -1;
}

QPoint Circle::getCenter(){
    return center;
}

int Circle::getRadius(){
    return radius;
}

int Circle::getWidth(){
    return width;
}

void Circle::setCenter(int x, int y){
    center.setX(x);
    center.setY(y);
}

void Circle::setRadius(int rad){
    this->radius = rad;
}

void Circle::setWidth(int wh){
    this->width = wh;
}

void Circle::clear(){
    radius = -1;
}

void Circle::draw(QImage &image){
    if(radius != -1){
        int x1 = center.x();
        int y1 = center.y();
        int x = 0;
        int y = radius;
        int delta = 1 - 2 * radius;
        int error = 0;
        while (y >= 0){
            image.setPixel(x1 + x, y1 + y, qRgb(0, 0, 0));
            image.setPixel(x1 + x, y1 - y, qRgb(0, 0, 0));
            image.setPixel(x1 - x, y1 + y, qRgb(0, 0, 0));
            image.setPixel(x1 - x, y1 - y, qRgb(0, 0, 0));
            error = 2 * (delta + y) - 1;
            if ((delta < 0) && (error <= 0)){
                delta += 2 * ++x + 1;
                continue;
            }
            if ((delta > 0) && (error > 0)){
                delta -= 2 * --y + 1;
                continue;
            }
            delta += 2 * (++x - y--);
        }
    }
}

Circle::~Circle(){}

void Circle::writeToFile(QTextStream &stream){
    stream << "Circle\n";
    stream << center.x() << " " << center.y() << " " << radius << '\n';
    stream << '\n';
}

QVector<int> Circle::parseLine(QString line){
    QVector<int> args;
    QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    args.append(list[0].toInt());
    args.append(list[1].toInt());
    args.append(list[2].toInt());
    return args;
}

IDraw* Circle::readFromFile(QTextStream &stream){
    QVector<int> args;
    QString line;
    while(!stream.atEnd()){
        line = stream.readLine();
        if(line.isEmpty())
            break;
        args = parseLine(line);
        center.setX(args[0]);
        center.setY(args[1]);
        radius = args[2];
    }
    return this;
}
