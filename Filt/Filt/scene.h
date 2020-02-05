#ifndef SCENE_H
#define SCENE_H

#include <QImage>

#include "imageeditor.h"

class Scene: public QObject
{
    Q_OBJECT
private:
    ImageEditor editor;
    QImage *sourceImage;
    QImage *destImage;

public:
    Scene();

    Scene(QImage* src, QImage* dst);

    void toBW();

    void openImage(QString filename);

    void copySrcToDst();

    void copyDstToSrc();

    bool saveImageDst(QString filename);

    void negative();

    void blur();

    void sharp();

    void embossing();

    void pathSelection(int shift);

    void aquarell();

    void gammaCorrection(double gamma);

    void identTransform();

    void customMatrixFilt(QVector<QVector<int>> matrix, int div, int shift, bool autoDiv);

    void pixel();

Q_SIGNALS:
    void sceneUpd();
};

#endif // SCENE_H
