#ifndef PURCHASEFORM_H
#define PURCHASEFORM_H

#include <QWidget>

//#include <CustomComboBox.h>


namespace Ui {
class PurchaseForm;
}

class PurchaseForm : public QWidget
{
    Q_OBJECT

public:
    explicit PurchaseForm(QString selected_City, QWidget *parent = nullptr);
    ~PurchaseForm();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::PurchaseForm *ui;
};

#endif // PURCHASEFORM_H
