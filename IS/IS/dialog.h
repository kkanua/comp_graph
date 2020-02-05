#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT


private:
    Ui::Dialog *ui;
    double minY;
    double maxY;
    double minX;
    double maxX;
    double net_k;
    double net_m;


public:
    double getMinY();
    double getMinX();
    double getMaxY();
    double getMaxX();
    double getNet_k();
    double getNet_m();

    explicit Dialog(QWidget *parent = nullptr);

    //void showEvent(QShowEvent *) override;
    ~Dialog();

Q_SIGNALS:
    void updatedParams();

private slots:

    void on_buttonBox_accepted();
};

#endif // DIALOG_H
