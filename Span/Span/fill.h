#ifndef FILL_H
#define FILL_H

#include <QImage>
#include <QColor>
#include <stack>

#define WIDTH 2000
#define HEIGHT 2000

#include "idraw.h"

class Fill: public IDraw
{
private:
    QPoint seed;
    int color;
    int cohension;

    bool sameColor(QRgb color, int codeColor);

    QRgb decodeColor(int codeColor);

    int codeColor(QRgb color);

    void spanFill(int x0, int y0, int oldColor, int newColor, QImage& image);
    
    void addSpan(int x, int y, int oldColor, std::stack<QLine>& spans, QImage& image);
    
    void fillLine(QLine& span, int newColor, QImage& image);
    
    void addNeighbours(QLine& span, std::stack<QLine>& spans, int oldColor, QImage& image);

    QVector<int> parseLine(QString line);

public:
    Fill();

    Fill(int x, int y, int color, int cohension);

    void setSeed(int x, int y);

    void setColor(int color);

    void draw(QImage& image);

    void writeToFile(QTextStream &stream);

    IDraw * readFromFile(QTextStream &stream);
};



#endif // FILL_H
