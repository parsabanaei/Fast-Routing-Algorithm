#include "popupwindowpurchaseitems.h"
#include "ui_popupwindowpurchaseitems.h"
#include "dbhandler.h"

#include "CustomComboBox.h"

void showFoods(Ui::PopupWindowPurchaseItems* ui, QString cityName);
QString selectedCity;
GlobalData globalData;



PopupWindowPurchaseItems::PopupWindowPurchaseItems(QString selected_City,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PopupWindowPurchaseItems)
{
    ui->setupUi(this);

    selectedCity = selected_City;

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
     showFoods(ui,selectedCity);
}



PopupWindowPurchaseItems::~PopupWindowPurchaseItems()
{
    delete ui;
}

void PopupWindowPurchaseItems::on_pushButton_3_clicked()
{
    close();
}


void PopupWindowPurchaseItems::on_pushButton_2_clicked()
{

    QMessageBox msgBox;
   // QSqlQuery qry;
   //QSqlQuery query;
    QString city;
    QString food;
    QString price;
    QString quantity;
    QString totalPriceStr;


    msgBox.setText(QString::number(globalData._vector.size()));
    msgBox.exec();


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {

        QString str="";
        double totalPrice;
        str += "Purchased Items:\n\n";
        for(int i=0;i<globalData._vector.size();i++)
        {
             city = globalData._vector[i].city;
             food = globalData._vector[i].food;
             price = QString::number(globalData._vector[i].price);
             quantity = QString::number(globalData._vector[i].quantity);


            str +="ID:  " + QString::number(globalData._vector[i].id)+" \n";
            str +="City:  " + city+" \n";
            str +="Food:  " + food+" \n";
            str +="Price:  " + price+"$ US \n";
            str +="Quntity:  " + quantity+" \n";
            totalPrice = globalData._vector[i].price*globalData._vector[i].quantity;
            totalPriceStr = QString::number(totalPrice);
            str +="Total Pricce:  " + totalPriceStr+"$ US \n";
            str += "\n\n\n";

                QSqlQuery query;
                query.prepare("INSERT INTO Purchase_History (City_Name, Food_Name, Price, Quantity, Total_Price) "
                              "VALUES (:City_Name, :Food_Name, :Price, :Quantity, :Total_Price)");
                query.bindValue(":City_Name", city);
                query.bindValue(":Food_Name", food);
                query.bindValue(":Price", price);
                query.bindValue(":Quantity", quantity);
                query.bindValue(":Total_Price", totalPriceStr);
                query.exec();

        }
        msgBox.setText(str);
        msgBox.exec();




        dbHandler.close();
        //showFoods(ui);
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}



void showFoods(Ui::PopupWindowPurchaseItems* ui, QString cityName)
{
    QMessageBox msgBox;
    QString city,food;
    double price;
    int id;
    int row = 0;
    int column = 0;
   // QTableWidgetItem *item = new QTableWidgetItem;

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(47);


    QStringList labels = { "City Name","Traditional Food", "Price", "Quantity" };
    ui->tableWidget->setHorizontalHeaderLabels(labels);


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQuery query1("SELECT ID, City, Food, Price FROM Foods WHERE City LIKE '%"+cityName+"%'");

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

