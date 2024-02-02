#ifndef STARTINGFROMPARIS_H
#define STARTINGFROMPARIS_H

#include <QMainWindow>

#include <QMainWindow>

namespace Ui
{
  class startingFromParis;
}
class startingFromParis : public QMainWindow
{
    Q_OBJECT
public:
    //constructor
    explicit startingFromParis(QWidget *parent = nullptr);

    //destructor
    ~startingFromParis();

signals:
private slots:
    void on_pushButton_enterNumOfCities_clicked();
    //void on_pushButton_purchaseFood_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui :: startingFromParis * ui;

};

#endif // STARTINGFROMPARIS_H
