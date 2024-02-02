#ifndef EUROPEANCITIES_H
#define EUROPEANCITIES_H

#include <QMainWindow>


namespace Ui {
class EuropeanCities;
}

class EuropeanCities : public QMainWindow
{
    Q_OBJECT

public:
    explicit EuropeanCities(QWidget *parent = nullptr);
    ~EuropeanCities();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);


private:
    Ui::EuropeanCities *ui;
};

#endif // EUROPEANCITIES_H
