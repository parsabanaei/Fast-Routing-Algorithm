#ifndef TRADITIONALFOOD_H
#define TRADITIONALFOOD_H

#include <QMainWindow>
#include "ui_traditionalFood.h"

namespace Ui
{
    class traditionalFood;
}

class traditionalFood : public QMainWindow
{
    Q_OBJECT

public:
    // constructor
    explicit traditionalFood(QWidget *parent = nullptr);
    //destructor
    ~traditionalFood();

private slots:
    void on_pushButton_selectCity_clicked();

private:
    Ui::traditionalFood *ui;
};


#endif // TRADITIONALFOOD_H
