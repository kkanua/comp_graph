    #ifndef POLYLINE_H
#define POLYLINE_H
#include <QPoint>
#include <QVector>

class Polyline
{
private:
    QVector<QPoint> polylineCoordinates;

    void drawLine(int x0, int y0, int x1, int y1);

public:
    Polyline();

    QVector<QPoint>& getPolylineCoordinates();

    void setPolylineCoordinates(int x_start, int y_start, int x_end, int y_end);

    void addCoordinates(int new_x, int new_y);

    void addCorrdinates(QPoint point);

    void removeLastPoint();

    void removeLine();
};

#endif // POLYLINE_H
