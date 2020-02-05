#ifndef IDRAW_H
#define IDRAW_H

#include <QImage>
#include <QTextStream>

class IDraw
{
public:
    IDraw();

    virtual void draw(QImage& image) = 0;

    virtual void writeToFile(QTextStream& stream) = 0;

    virtual IDraw* readFromFile(QTextStream& stream) = 0;

    virtual ~IDraw();
};

#endif // IDRAW_H
