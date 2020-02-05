#ifndef MATRIXSETUP_H
#define MATRIXSETUP_H

#include <QDialog>

namespace Ui {
class matrixSetup;
}

class matrixSetup : public QDialog
{
    Q_OBJECT

private:
    Ui::matrixSetup *ui;
    QVector<QVector<int>> matrix;
    int div;
    int shift;
    bool autoDiv;

public:
    explicit matrixSetup(QWidget *parent = nullptr);

    QVector<QVector<int>> getMatrix();

    int getDiv();

    int getShift();

    bool getAutoDiv();

    ~matrixSetup();

Q_SIGNALS:
    void matrixUpdated();

private slots:
    void on_buttonBox_accepted();
};

#endif // MATRIXSETUP_H
