#include "polyline.h"

Polyline::Polyline(){}


QVector<QPoint>& Polyline::getPolylineCoordinates(){
    return polylineCoordinates;
}

void Polyline::setPolylineCoordinates(int x_start, int y_start, int x_end, int y_end){
    QPoint begin(x_start, y_start);
    QPoint end(x_end, y_end);
    polylineCoordinates.append(begin);
    polylineCoordinates.append(end);
}

void Polyline::addCoordinates(int new_x, int new_y){
    QPoint point(new_x, new_y);
    polylineCoordinates.append(point);
}

void Polyline::addCorrdinates(QPoint point){
    polylineCoordinates.append(point);
}

//check if empty vector
void Polyline::removeLastPoint(){
    //std::cout << polylineCoordinates.length() << std::endl;
    polylineCoordinates.remove(polylineCoordinates.length() - 1);
}

void Polyline::removeLine(){
    polylineCoordinates.clear();
}
