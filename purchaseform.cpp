#include "purchaseform.h"
#include "ui_purchaseform.h"

#include "dbhandler.h"
#include "CustomComboBox.h"
//#include <CustomComboBox.cpp>


void showFoods(Ui::PurchaseForm* ui, QString cityName);
QString selectedCity;
//GlobalData globalData;


PurchaseForm::PurchaseForm(QString selected_City, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PurchaseForm)
{
    ui->setupUi(this);


    selectedCity = selected_City;

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
     showFoods(ui,selectedCity);

}

PurchaseForm::~PurchaseForm()
{
    delete ui;
}

void PurchaseForm::on_pushButton_4_clicked()
{
    // close Button
    QWidget::close();
}




void PurchaseForm::on_pushButton_2_clicked()
{
    CustomComboBox ccb;
    ccb.purchaseItems();
}






void showFoods(Ui::PurchaseForm* ui, QString cityName)
{
    QMessageBox msgBox;
    QString city,food;
    double price;
    int id;
    int row = 0;
    int column = 0;
   // QTableWidgetItem *item = new QTableWidgetItem;

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(60);


    QStringList labels = { "City Name","Traditional Food", "Price", "Quantity" };
    ui->tableWidget->setHorizontalHeaderLabels(labels);


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQuery query1("SELECT ID, City, Food, Price FROM Foods WHERE City LIKE '%"+cityName+"%' AND IsActive=1 AND IsFoodActive=1");

                    while(query1.next())
                    {
                        id = query1.value(0).toInt();
                        city = query1.value(1).toString();
                        food = query1.value(2).toString();
                        price = query1.value(3).toDouble();

                       // item = new QTableWidgetItem();
                        //item->setText(city);

                       // ui->tableWidget->setItem(row,column++,item);

                        ui->tableWidget->setItem(row,column++,new QTableWidgetItem(city));

                        ui->tableWidget->setItem(row,column++,new QTableWidgetItem(food));

                        ui->tableWidget->setItem(row,column++,new QTableWidgetItem(QString::number(price)));



                        //**************************************************

                        CustomComboBox* _customComboBox = new CustomComboBox(id,city,food,price);

                        for(int i=0;i<=20;i++)
                            _customComboBox->addItem(QString::number(i));

                        ui->tableWidget->setCellWidget(row,column++,_customComboBox);


                        //**************************************************


                        column = 0;
                        row++;
                    }


        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}





