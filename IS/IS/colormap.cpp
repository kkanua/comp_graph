#include "colormap.h"
#include <iostream>

ColorMap::ColorMap(){}

void ColorMap::draw(QImage &image, QImage& imageVals, double(*f)(double, double)){
    double value;
    QPainter writer(&imageVals);
    QVector<double> minMax = maxAndMin(image, Function::f);
    double max = minMax[0];
    double min = minMax[1];

    int step_write = image.height() / numOfValues + 2;
    double step = abs(max - min) / numOfValues;
    int j = 0;

    writer.setPen(isoColor);
    writer.setFont(QFont("Times", 10, QFont::Bold));
    for(int i = 1; i < imageVals.height(); i+= step_write){
        if(j == 0){
            j++;
            continue;
        }
        if(f == &Function::f)
            writer.drawText(QPoint(0, i), QString::number(y(i, image), 'f', 2));
        else
            writer.drawText(QPoint(0, i), QString::number(max - j*step, 'f', 2));
        j++;
    }

    minMax = maxAndMin(image, f);
    max = minMax[0];
    min = minMax[1];

    step = abs(max - min) / numOfValues;
    int i = 0;
    for(int u = 0; u != image.width(); u++){
        for(int v = 0; v != image.height(); v++){
            value = f(x(u, image), y(v, image));
            i = 0;
            for(double pos = min; pos <= max; pos += step){
                if((value > pos) && (value <= pos + step)){
                    image.setPixelColor(u, v, colors[i]);
                    break;
                }
                i++;
            }
        }
    }
    setIsolinesLevels(min, max);
}




//void ColorMap::drawInterpolation(QImage &image, bool dithering, double (*f)(double, double)){
//    double r, g, b;
//    QRgb pixColor;
//    double f_value;
//    int idx;
//    QVector<QVector<double>> err(image.width(), QVector<double>(3, 0));
//    QVector<QVector<double>> curr_err_row(image.width(), QVector<double>(3, 0));
//    QVector<QVector<double>> temp_err(colors.length());
//    QVector<double> total_err;
//    double r_err, g_err, b_err;
//    double error_scale = 16;

//    QVector<double> mAm = maxAndMin(image, f);
//    setIsolinesLevels(mAm[1], mAm[0]);


//    for(int u = 1; u != image.width() - 1; u++){
//        for(int v = 1; v != image.height() - 1; v++){
//            pixColor = image.pixel(u, v);
//            f_value = f(x(u), y(v));
//            idx = getIsolineIdx(f_value);
//            if(isolinesLevels.length() - 1 == idx)
//                continue;
//            r = colors[idx].red() + (f_value - isolinesLevels[idx]) * ( colors[idx + 1].red() - colors[idx].red() ) / (isolinesLevels[idx + 1] - isolinesLevels[idx]);
//            g = colors[idx].green() + (f_value - isolinesLevels[idx]) * ( colors[idx + 1].green() - colors[idx].green() ) / (isolinesLevels[idx + 1] - isolinesLevels[idx]);
//            b = colors[idx].blue() + (f_value - isolinesLevels[idx]) * ( colors[idx + 1].blue() - colors[idx].blue() ) / (isolinesLevels[idx + 1] - isolinesLevels[idx]);
//            image.setPixel(u, v, qRgb(r, g, b));
//        }
//    }

//    if(dithering){
//        for(int v = 1; v != image.height() - 1; v++){

//            curr_err_row = err;
//            err.clear();
//            err.resize(image.width());
//            for(int i = 0; i != image.width(); i++){
//                err[i].append(0);
//                err[i].append(0);
//                err[i].append(0);
//            }

//            for(int u = 1; u != image.width() - 1; u++){
//                pixColor = image.pixel(u, v);
//                idx = 0;
//                for(int i = 0; i != colors.length(); i++){
//                    temp_err[i].append((qRed(pixColor) + curr_err_row[u][0] - colors[i].red()) );
//                    temp_err[i].append((qGreen(pixColor) + curr_err_row[u][1]) - colors[i].green());
//                    temp_err[i].append((qBlue(pixColor)  + curr_err_row[u][2]) - colors[i].blue() );
//                    //total_err.append(30 * pow(temp_err[i][0], 2) + 59 * pow(temp_err[i][1], 2) + 11*pow(temp_err[i][2], 2));
//                    total_err.append(sqrt(pow(temp_err[i][0], 2) + pow(temp_err[i][1], 2) + pow(temp_err[i][2], 2)));
//                    idx = total_err[i] < total_err[idx] ? i : idx;
//                }

//                r_err = temp_err[idx][0];
//                g_err = temp_err[idx][1];
//                b_err = temp_err[idx][2];

//                curr_err_row[u + 1][0] += r_err * 7 / error_scale;
//                curr_err_row[u + 1][1] += g_err * 7 / error_scale;
//                curr_err_row[u + 1][2] += b_err * 7 / error_scale;
//                err[u][0] += r_err * 5 / error_scale;
//                err[u][1] += g_err * 5 / error_scale;
//                err[u][2] += b_err * 5 / error_scale;
//                err[u + 1][0] += r_err * 1 / error_scale;
//                err[u + 1][1] += g_err * 1 / error_scale;
//                err[u + 1][2] += b_err * 1 / error_scale;
//                err[u - 1][0] += r_err * 3 / error_scale;
//                err[u - 1][1] += g_err * 3 / error_scale;
//                err[u - 1][2] += b_err * 3 / error_scale;

//                image.setPixel(u, v, colors[idx].rgb());

//                total_err.clear();
//                temp_err.clear();
//                temp_err.resize(colors.length());
//            }
//        }
//    }
//}


void ColorMap::drawIsoline(QImage &image, QVector<double> isolines, double(*f)(double, double)){
    QVector<QPoint> points;
    QPainter painter(&image);
    painter.setPen(isoColor);
    int step_u = image.width() / net_k < 1 ? 1 : image.width() / net_k;
    int step_v = image.height() / net_m < 1 ? 1: image.height() / net_m;
    double f1, f2, f3, f4;

    for(double isoline: isolines){
        for(int u = 1; u < image.width() - 1; u += step_u){
            for(int v = 1; v < image.height() - 1; v += step_v){
                points.clear();
                f1 = f(x(u, image), y(v, image));
                f2 = f(x(u + step_u, image), y(v, image));
                f3 = f(x(u, image), y(v + step_v, image));
                f4 = f(x(u + step_u, image), y(v + step_v, image));
                if((isoline >= f1 && isoline < f2) || (isoline <= f1 && isoline > f2))
                    points.append(QPoint(u + step_u * (isoline - f1) / (f2 - f1), v));
                if((isoline >= f2 && isoline < f4) || (isoline <= f2 && isoline > f4))
                    points.append(QPoint(u + step_u, v + step_v * (isoline - f2) / (f4 - f2)));
                if((isoline > f1 && isoline <= f3) || (isoline < f1 && isoline >= f3))
                    points.append(QPoint(u, v + step_v * (isoline - f1) / (f3 - f1)));
                if((isoline > f3 && isoline <= f4) || (isoline < f3 && isoline >= f4))
                    points.append(QPoint(u + step_u * (isoline - f3) / (f4 - f3), v + step_v));

                if(points.length() == 4){
                    double f5 = (f1 + f2 + f3 + f4) / 4.;
                    if((isoline > f1 && isoline <= f5) || (isoline < f1 && isoline >= f5))
                        std::swap(points[1], points[2]);
                    painter.drawLine(points[0], points[1]);
                    painter.drawLine(points[2], points[3]);
                }
                if(points.length() == 2)
                    painter.drawLine(points[0], points[1]);
            }
        }
    }
}

void ColorMap::setParams(QVector<double> params){
    if(params[0] > params[2] && params[1] > params[3]){
        maxX = params[0];
        maxY = params[1];
        minX = params[2];
        minY = params[3];
        net_k = params[4];
        net_m = params[5];
    }
}

void ColorMap::recalculate(QImage &image, QImage& imageVals, double(*f)(double, double)){
    isolinesLevels.clear();
    draw(image, imageVals, f);
}

void ColorMap::setIsolinesLevels(double min, double max){
    isolinesLevels.clear();
    double step = (max - min) / numOfValues;
    for(int i = 1; i <= numOfValues; i++)
        isolinesLevels.append(min + i * step);
}

double ColorMap::x(int u, QImage& image){
    return (maxX - minX) / (image.width()) * u + minX;
}

double ColorMap::y(int v, QImage& image){
    return (maxY - minY) / (image.height()) * (image.height() - v)  + minY;
}

int ColorMap::u(double x, QImage& image){
    return static_cast<int>(round(image.width() / (maxX - minX) * (x - minX) + 0.5));
}

int ColorMap::v(double y, QImage& image){
    return static_cast<int>(round(image.height() / (maxY - minY) * (y - minY) + 0.5));
}

int ColorMap::getIsolineIdx(double f_value){
    for(int i = 0; i != isolinesLevels.length() - 1; i++){
        if(f_value >= isolinesLevels[i] && f_value < isolinesLevels[i + 1])
            return i;
    }
    return isolinesLevels.length() - 1;
}

QVector<double> ColorMap::maxAndMin(QImage& image, double(*f)(double, double)){
    QVector<double> maxAndMin;
    double min = f(x(0, image), y(0, image));
    double max = f(x(0, image), y(0, image));
    double val;

    for(int u = 0; u != image.width(); u++){
        for(int v = 0; v != image.height(); v++){
            val = f(x(u, image), y(v, image));
            min = (val < min) ? val : min;
            max = (val > max) ? val : max;
        }
    }
    maxAndMin.append(max);
    maxAndMin.append(min);
    return maxAndMin;
}

QVector<double> ColorMap::getIsolineLevels(QImage& image, double(*f)(double, double)){
    QVector<double> IS;
    QVector<double> mAm = maxAndMin(image, f);

    double step = (mAm[0] - mAm[1]) / numOfValues;
    for(int i = 1; i <= numOfValues; i++)
        IS.append(mAm[1] + i * step);
    return IS;
}

void ColorMap::drawGrid(QImage &image){
    QPainter painter(&image);
    painter.setPen(Qt::black);

    int step_u = image.width() / net_k < 1 ? 1 : image.width() / net_k;
    int step_v = image.height() / net_m < 1 ? 1: image.height() / net_m;

    for(int u = 0; u <= image.width(); u += step_u)
        painter.drawLine(u, 0, u, image.height());
    for(int v = 0; v <= image.height(); v += step_v)
        painter.drawLine(0, v, image.width(), v);
}

void ColorMap::setNumberOfLevels(int num){
    numOfValues = num;
}

void ColorMap::setColors(QVector<QColor> col){
    colors = col;
}

void ColorMap::setIsoColor(QColor color){
    isoColor = color;
}











void ColorMap::drawInterpolation(QImage &image, bool dithering, double (*f)(double, double)){
    double r, g, b;
    QRgb pixColor;
    double f_value;
    int idx;
    double std_err, std_tmp_err;
    double tmp_eRed, tmp_eGreen, tmp_eBlue;
    double r_err, g_err, b_err;
    //double r_val, g_val, b_val;
    double error_scale = 16;

    QVector<double> mAm = maxAndMin(image, f);
    setIsolinesLevels(mAm[1], mAm[0]);


    for(int u = 1; u != image.width() - 1; u++){
        for(int v = 0; v != image.height() - 1; v++){
            pixColor = image.pixel(u, v);
            f_value = f(x(u, image), y(v, image));
            idx = getIsolineIdx(f_value);
            if(isolinesLevels.length() - 1 == idx)
                continue;
            r = colors[idx].red() + (f_value - isolinesLevels[idx]) * ( colors[idx + 1].red() - colors[idx].red() ) / (isolinesLevels[idx + 1] - isolinesLevels[idx]);
            g = colors[idx].green() + (f_value - isolinesLevels[idx]) * ( colors[idx + 1].green() - colors[idx].green() ) / (isolinesLevels[idx + 1] - isolinesLevels[idx]);
            b = colors[idx].blue() + (f_value - isolinesLevels[idx]) * ( colors[idx + 1].blue() - colors[idx].blue() ) / (isolinesLevels[idx + 1] - isolinesLevels[idx]);
            image.setPixel(u, v, qRgb(r, g, b));
        }
    }

    if(dithering){
        for(int v = 0; v != image.height() - 1; v++){
            for(int u = 1; u != image.width() - 1; u++){
                pixColor = image.pixel(u, v);
                idx = 0;
                std_err = 1000000;
                for(int i = 0; i != colors.length(); i++){
                    tmp_eRed = qRed(pixColor) - colors[i].red();
                    tmp_eGreen = qGreen(pixColor) - colors[i].green();
                    tmp_eBlue = qBlue(pixColor) - colors[i].blue();
                    std_tmp_err = sqrt(tmp_eRed * tmp_eRed + tmp_eGreen * tmp_eGreen + tmp_eBlue * tmp_eBlue);
                    if(std_tmp_err < std_err){
                        idx = i;
                        r_err = tmp_eRed;
                        g_err = tmp_eGreen;
                        b_err = tmp_eBlue;
                        std_err = std_tmp_err;
                    }
                }


                pixColor = image.pixel(u + 1,v);
                image.setPixel(u + 1, v, qRgb(r_err * 3 / error_scale + qRed(pixColor), g_err * 3 / error_scale + qGreen(pixColor), b_err * 3 / error_scale + qBlue(pixColor)));

                pixColor = image.pixel(u + 1,v + 1);
                image.setPixel(u + 1, v + 1, qRgb(r_err * 3 / error_scale + qRed(pixColor), g_err * 3 / error_scale + qGreen(pixColor), b_err * 3 / error_scale + qBlue(pixColor)));

                pixColor = image.pixel(u, v + 1);
                image.setPixel(u, v + 1, qRgb(r_err * 3 / error_scale + qRed(pixColor), g_err * 3 / error_scale + qGreen(pixColor), b_err * 3 / error_scale + qBlue(pixColor)));

                pixColor = image.pixel(u - 1, v + 1);
                image.setPixel(u - 1, v + 1, qRgb(r_err * 3 / error_scale + qRed(pixColor), g_err * 3 / error_scale + qGreen(pixColor), b_err * 3 / error_scale + qBlue(pixColor)));

                image.setPixel(u, v, colors[idx].rgb());
            }
        }
    }
}
