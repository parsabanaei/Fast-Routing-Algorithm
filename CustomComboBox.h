#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <QMessageBox>
#include "GlobalVector.h"




class CustomComboBox : public QComboBox
{
    Q_OBJECT


public:

    //CustomComboBox(QVector<T>* _vector,int _id, QString _city, QString _food, double _price);
    CustomComboBox(int _id, QString _city, QString _food, double _price);
    CustomComboBox();
    void purchaseItems();



public slots:
    void onCurrentIndexChanged(int value);


private:
    QString city, food;
    double price;
    int id;
    QMessageBox msgBox;
    //GlobalData globalData;
};

#endif // CUSTOMCOMBOBOX_H
