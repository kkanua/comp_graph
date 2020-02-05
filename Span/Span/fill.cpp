#include "fill.h"
#include <iostream>

Fill::Fill(){
}

Fill::Fill(int x, int y, int color, int cohension){
    seed.setX(x);
    seed.setY(y);
    this->cohension = cohension;
    this->color = color;
}

void Fill::setSeed(int x, int y){
    seed.setX(x);
    seed.setY(y);
}

void Fill::setColor(int color){
    this->color = color;
}

bool Fill::sameColor(QRgb color, int codeColor){
    if((codeColor == 1) && (color == qRgb(0, 0, 0)))
        return true;
    if((codeColor == 0) && (color == qRgb(255, 255, 255)))
        return true;
    return false;
}

int Fill::codeColor(QRgb color){
    if(color == qRgb(0, 0, 0))
        return 1;
    if(color == qRgb(255, 255, 255))
        return 0;
}

QRgb Fill::decodeColor(int codeColor){
    if(codeColor == 1)
        return qRgb(0, 0, 0);
    if(codeColor == 0)
        return qRgb(255, 255, 255);
}

void Fill::draw(QImage &image){
    spanFill(seed.x(), seed.y(), codeColor(image.pixel(seed.x(), seed.y())), color, image);
}

void Fill::spanFill(int x0, int y0, int oldColor, int newColor, QImage &image){
    if(newColor == oldColor)
        return;
    std::stack<QLine> spans;
    QLine currentSpan;
    addSpan(x0, y0, oldColor, spans, image);
    while(!spans.empty()){
        currentSpan = spans.top();
        spans.pop();
        fillLine(currentSpan, newColor, image);
        addNeighbours(currentSpan, spans, oldColor, image);
    }
}

void Fill::addSpan(int x, int y, int oldColor, std::stack<QLine>& spans, QImage& image){
    int leftBorder = -1;
    int rightBorder = -1;
    
    for(int xLeft = x - 1; ; xLeft--){
        if(xLeft <= 0){
            leftBorder = 0;
            break;
        }
        
        if(codeColor(image.pixel(xLeft, y)) != oldColor){
            leftBorder = xLeft + 1;
            break;
        }
    }
    
    for(int xRight = x + 1; ; xRight++){
        if(xRight >= WIDTH){
            rightBorder = WIDTH - 1;
            break;
        }
        
        if(codeColor(image.pixel(xRight, y)) != oldColor){
            rightBorder = xRight - 1;
            break;
        }
    }
    spans.push(*(new QLine(leftBorder, y, rightBorder, y)));
}

void Fill::fillLine(QLine& span, int newColor, QImage& image){
    int y = span.y1();
    for(int x = span.x1(); x <= span.x2(); x++)
        image.setPixel(x, y, decodeColor(newColor));
}

void Fill::addNeighbours(QLine& span, std::stack<QLine>& spans, int oldColor, QImage& image){
    int xRightUpperSpan = -1;
    int xRightDownSpan = -1;
    
    for(int x = span.x1(), yUp = span.y1() + 1; x < span.x2();){
        
        if(yUp >= HEIGHT) break;
        
        if(codeColor(image.pixel(x, yUp)) == oldColor){
            addSpan(x, yUp, oldColor, spans, image);
            xRightUpperSpan = spans.top().x2();
        }
        if((xRightUpperSpan != -1) && (x < xRightUpperSpan) && (span.x2() > xRightUpperSpan))
            x = xRightUpperSpan + 1;
        else x++;
        
        if(xRightUpperSpan >= span.x2())
            break;
    }

    for(int x = span.x1(), yDown = span.y1() - 1; x < span.x2();){
        
        if(yDown <= 0) break;
        
        if(codeColor(image.pixel(x, yDown)) == oldColor){
            addSpan(x, yDown, oldColor, spans, image);
            xRightDownSpan = spans.top().x2();
        }
        if((xRightDownSpan != -1) && (x < xRightDownSpan) && (span.x2() > xRightDownSpan))
            x = xRightDownSpan + 1;
        else x++;
        
        if(xRightDownSpan >= span.x2())
            break;
    }
    
    if(cohension == 4) return;
    
    if((span.x2() < WIDTH - 1) && (span.y1() < HEIGHT - 1)){
        if(codeColor(image.pixel(span.x2() + 1, span.y1() + 1)) == oldColor)
            addSpan(span.x2() + 1, span.y1() + 1, oldColor, spans, image);
    }
    
    if((span.x1() > 1) && (span.y1() < HEIGHT - 1)){
        if(codeColor(image.pixel(span.x1() - 1, span.y1() + 1)) == oldColor)
            addSpan(span.x1() - 1, span.y1() + 1, oldColor, spans, image);
    }
    
    if((span.x1() > 1) && (span.y1() > 1)){
        if(codeColor(image.pixel(span.x1() - 1, span.y1() - 1)) == oldColor)
            addSpan(span.x1() - 1, span.y1() - 1, oldColor, spans, image);
    }
    
    if((span.x2() + 1 < WIDTH) && (span.y1() > 1)){
        if(codeColor(image.pixel(span.x2() + 1, span.y1() - 1)) == oldColor)
            addSpan(span.x2() + 1, span.y1() - 1, oldColor, spans, image);
    }
}


void Fill::writeToFile(QTextStream &stream){
    stream << "Fill\n";
    stream << seed.x() << " " << seed.y() << " " << color << " " << cohension << '\n';
    stream << '\n';
}

QVector<int> Fill::parseLine(QString line){
    QVector<int> args;
    QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    args.append(list[0].toInt());
    args.append(list[1].toInt());
    args.append(list[2].toInt());
    args.append(list[3].toInt());
    return args;
}

IDraw* Fill::readFromFile(QTextStream &stream){
    QVector<int> args;
    QString line;
    while(!stream.atEnd()){
        line = stream.readLine();
        if(line.isEmpty()) break;
        args = parseLine(line);
        seed.setX(args[0]);
        seed.setY(args[1]);
        color = args[2];
        cohension = args[3];
    }
    return this;
}

/*
QVector<QLine> spans;
QPoint start;
QPoint end;
int y = y0;
bool leftFound = false;
bool rightFound = false;
while(true){
    for(int xLeft = x0 - 1, xRight = x0 + 1; ; xLeft--, xRight++){

        if(codeColor(image.pixel(xLeft, y0)) == oldcolor && !leftFound){
            start.setX(xLeft);
            start.setY(y);
        }

        if(codeColor(image.pixel(xRight, y0)) == oldcolor && !rightFound){
            end.setX(xLeft);
            end.setY(y);
        }
    }
}
*/
