#ifndef POPUPWINDOWPURCHASEITEMS_H
#define POPUPWINDOWPURCHASEITEMS_H

#include <QMainWindow>

namespace Ui {
class PopupWindowPurchaseItems;
}

class PopupWindowPurchaseItems : public QMainWindow
{
    Q_OBJECT

public:
    explicit PopupWindowPurchaseItems(QString selected_City,QWidget *parent = nullptr);
    ~PopupWindowPurchaseItems();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::PopupWindowPurchaseItems *ui;
};

#endif // POPUPWINDOWPURCHASEITEMS_H
