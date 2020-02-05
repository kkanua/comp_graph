#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <QImage>
#include <math.h>

class ImageEditor
{
public:
    ImageEditor();

    void toBW(QImage& sourceImage, QImage& destImage);

    void matrixTransform(QVector<QVector<int>> matrix, int div, int shift, bool autoDiv, QImage& sourceImage, QImage& destImage);

    void negative(QImage& sourceImage, QImage& destImage);

    void medianFilt(QImage& sourceImage, QImage& destImage);

    void gammaCorrection(QImage& sourceImage, QImage& destImage, double gamma);

    void pixel(QImage& sourceImage, QImage& destImage);
};

#endif // IMAGEEDITOR_H
