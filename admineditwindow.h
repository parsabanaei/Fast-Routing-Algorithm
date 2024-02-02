#ifndef ADMINEDITWINDOW_H
#define ADMINEDITWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminEditWindow;
}

class AdminEditWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminEditWindow(QWidget *parent = nullptr);
    ~AdminEditWindow();

private slots:
    void on_add_city_button_clicked();

    void on_delete_city_button_clicked();

    void on_add_city_button_2_clicked();

    void on_add_food_button_clicked();

    void on_delete_food_button_clicked();

    void on_comboBoxDeleteFoodCities_currentIndexChanged(int index);

    void on_comboBoxDeleteFoodCities_currentTextChanged(const QString &arg1);

    void on_tableWidget_delete_food_cellDoubleClicked(int row, int column);

    void on_add_distance_button__clicked();

    void on_comboBoxDeleteDistances_currentIndexChanged(int index);

    void on_tableWidget_delete_distances_cellDoubleClicked(int row, int column);

    void on_delete_distances_button_clicked();

private:
    Ui::AdminEditWindow *ui;
};

#endif // ADMINEDITWINDOW_H
