#ifndef ADMINMAINTENANCE_H
#define ADMINMAINTENANCE_H

#include <QMainWindow>

namespace Ui {
class AdminMaintenance;
}

class AdminMaintenance : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMaintenance(QWidget *parent = nullptr);
    ~AdminMaintenance();

private slots:
    void on_add_city_button_clicked();

    void on_remove_city_button_clicked();

    void on_update_food_button_clicked();

    void on_comboBoxUpdateFoods_currentIndexChanged(int index);


    void on_tableWidget_update_food_cellDoubleClicked(int row, int column);

    void on_remove_food_button_clicked();

    void on_tableWidget_remove_food_cellDoubleClicked(int row, int column);

    void on_add_food_button_clicked();

    void on_tableWidget_add_food_cellDoubleClicked(int row, int column);


    void on_delete_purchase_history_button_clicked();

    void on_RefreshpushButton_clicked();

private:
    Ui::AdminMaintenance *ui;
};

#endif // ADMINMAINTENANCE_H
