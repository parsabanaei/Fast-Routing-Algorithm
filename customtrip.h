#ifndef CUSTOMTRIP_H
#define CUSTOMTRIP_H

#include <QMainWindow>

namespace Ui {
class CustomTrip;
}

class CustomTrip : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomTrip(QWidget *parent = nullptr);
    ~CustomTrip();

private slots:
    void on_comboBoxStartCity_currentIndexChanged(int index);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_pushButton_travel_efficiently_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::CustomTrip *ui;
};

#endif // CUSTOMTRIP_H
