#include "imageeditor.h"
#include <iostream>
#include <algorithm>
#include <numeric>

ImageEditor::ImageEditor(){

}

void ImageEditor::toBW(QImage& sourceImage, QImage& destImage){
    QRgb pixColor;
    int color;
    for(int u = 0; u != sourceImage.width(); u++){
        for(int v = 0; v != sourceImage.height(); v++){
            pixColor = sourceImage.pixel(u, v);
            color = 0.299 * qRed(pixColor) + 0.587 * qGreen(pixColor) + 0.114 * qBlue(pixColor);
            destImage.setPixel(u, v, qRgb(color, color, color));
        }
    }
}

void ImageEditor::matrixTransform(QVector<QVector<int>> matrix, int div, int shift, bool autoDiv, QImage &sourceImage, QImage &destImage){
    double r, g, b;
    int x, y;
    x= 0;
    y = 0;
    if(autoDiv){
        div = 0;
        for(int i = 0; i != matrix.length(); i++){
            for(int j = 0; j != matrix[i].length(); j++){
                div += matrix[i][j];
            }
        }
    }

    for(int v = 0; v != sourceImage.height(); v++){
        for(int u = 0; u != sourceImage.width(); u++){
            r = 0;
            g = 0;
            b = 0;
            for(int i = 0; i != matrix.length(); i++){
                for(int j = 0; j != matrix[i].length(); j++){
                    x = (u - 1 + j);
                    y = (v - 1 + i);

                    x = x < 0 ? 0 : x;
                    y = y < 0 ? 0 : y;

                    x = x >= sourceImage.width() ? sourceImage.width() - 1 : x;
                    y = y >= sourceImage.height() ? sourceImage.height() - 1 : y;

                    r += matrix[i][j] * qRed(sourceImage.pixel(x, y));
                    g += matrix[i][j] * qGreen(sourceImage.pixel(x, y));
                    b += matrix[i][j] * qBlue(sourceImage.pixel(x, y));
                }
            }
            r = r / div + shift;
            g = g / div + shift;
            b = b / div + shift;
            r = r > 255 ? 255 : r;
            g = g > 255 ? 255 : g;
            b = b > 255 ? 255 : b;

            r = r < 0 ? 0 : r;
            g = g < 0 ? 0 : g;
            b = b < 0 ? 0 : b;
            destImage.setPixel(u, v, qRgb(r, g, b));
        }
    }
}

void ImageEditor::negative(QImage &sourceImage, QImage &destImage){
    QRgb pixColor;
    for(int v = 0; v != sourceImage.height(); v++){
        for(int u = 0; u != sourceImage.width(); u++){
            pixColor = sourceImage.pixel(u, v);
            destImage.setPixel(u, v, qRgb(255 - qRed(pixColor), 255 - qGreen(pixColor), 255 - qBlue(pixColor)));
        }
    }
}

void ImageEditor::medianFilt(QImage &sourceImage, QImage &destImage){
    QVector<int> pixColorsR;
    QVector<int> pixColorsG;
    QVector<int> pixColorsB;
    int x, y;
    for(int v = 0; v != sourceImage.height(); v++){
        for(int u = 0; u != sourceImage.width(); u++){
            for(int j = -2; j != 3; j++){
                for(int i = -2; i != 3; i++){
                    x = u + i;
                    y = v + j;
                    x = x < 0 ? 0 : x;
                    y = y < 0 ? 0 : y;
                    x = x >= sourceImage.width() ? sourceImage.width() - 1 : x;
                    y = y >= sourceImage.height() ? sourceImage.height() - 1 : y;
                    pixColorsR.append(qRed(sourceImage.pixel(x, y)));
                    pixColorsG.append(qGreen(sourceImage.pixel(x, y)));
                    pixColorsB.append(qBlue(sourceImage.pixel(x, y)));

                }
            }
            std::sort(pixColorsR.begin(), pixColorsR.end());
            std::sort(pixColorsG.begin(), pixColorsG.end());
            std::sort(pixColorsB.begin(), pixColorsB.end());

            destImage.setPixel(u, v, qRgb(pixColorsR[12], pixColorsG[12], pixColorsB[12]));
            pixColorsR.clear();
            pixColorsG.clear();
            pixColorsB.clear();

        }
    }
}

void ImageEditor::gammaCorrection(QImage &sourceImage, QImage &destImage, double gamma){
    QRgb pixColor;
    double r, g, b;
    for(int v = 0; v != sourceImage.height(); v++){
        for(int u = 0; u != sourceImage.width(); u++){
            pixColor = sourceImage.pixel(u, v);
            r = pow(qRed(pixColor) / 255.0, gamma);
            g = pow(qGreen(pixColor) / 255.0, gamma);
            b = pow(qBlue(pixColor) / 255.0, gamma);
            destImage.setPixel(u, v, qRgb(r * 255., g * 255., b * 255.));
        }
    }
}

void ImageEditor::pixel(QImage &sourceImage, QImage &destImage){
    QRgb pixColor;
    int pixel_size = sourceImage.width() / 150;
    int x, y;
    int counter = 0;
    double avgR = 0, avgG = 0, avgB = 0;
    QVector<int> pixColorsR, pixColorsG, pixColorsB;

    for(int v = 0; v < sourceImage.height(); v += pixel_size){
        std::cout << v << std::endl;
        for(int u = 0; u < sourceImage.width(); u += pixel_size){
            for(int j = 0; j != pixel_size + 1; j++){
                for(int i = 0; i != pixel_size + 1; i++){
                    x = u + i;
                    y = v + j;
                    x = x < 0 ? 0 : x;
                    y = y < 0 ? 0 : y;
                    x = x >= sourceImage.width() ? sourceImage.width() - 1 : x;
                    y = y >= sourceImage.height() ? sourceImage.height() - 1 : y;
                    pixColor = sourceImage.pixel(x, y);
                    avgR += qRed(pixColor);
                    avgG += qGreen(pixColor);
                    avgB += qBlue(pixColor);
                    counter++;
                }
            }
            for(int j = 0; j != pixel_size + 1; j++){
                for(int i = 0; i != pixel_size + 1; i++){
                    x = u + i;
                    y = v + j;
                    x = x < 0 ? 0 : x;
                    y = y < 0 ? 0 : y;
                    x = x >= sourceImage.width() ? sourceImage.width() - 1 : x;
                    y = y >= sourceImage.height() ? sourceImage.height() - 1 : y;
                    destImage.setPixel(x, y, qRgb(avgR / counter, avgG / counter, avgB / counter));
                }
            }
            counter = 0;
            avgR = 0;
            avgG = 0;
            avgB = 0;
            pixColorsR.clear();
            pixColorsG.clear();
            pixColorsB.clear();
        }
    }
}
