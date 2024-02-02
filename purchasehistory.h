#ifndef PURCHASEHISTORY_H
#define PURCHASEHISTORY_H

#include <QMainWindow>

namespace Ui {
class PurchaseHistory;
}

class PurchaseHistory : public QMainWindow
{
    Q_OBJECT

public:
    explicit PurchaseHistory(QWidget *parent = nullptr);
    ~PurchaseHistory();

private slots:
    void on_pushButton_selectCity_clicked();

private:
    Ui::PurchaseHistory *ui;
};

#endif // PURCHASEHISTORY_H
