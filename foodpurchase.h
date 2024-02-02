#ifndef FOODPURCHASE_H
#define FOODPURCHASE_H

#include "QtWidgets/qtablewidget.h"
#include <QMainWindow>
#include "qtablewidget.h"
//#include "GlobalVector.h"


namespace Ui {
class FoodPurchase;
}

class FoodPurchase : public QMainWindow
{
    Q_OBJECT

public:
    explicit FoodPurchase(QWidget *parent = nullptr);
    ~FoodPurchase();




private slots:
    void on_pushButton_2_clicked();


private:
    Ui::FoodPurchase *ui;

};

#endif // FOODPURCHASE_H
