#include "purchasehistory.h"
#include "ui_purchasehistory.h"
#include "dbhandler.h"
//#include <QListView>
#include <QTableView>


void showReport(Ui::PurchaseHistory* ui);
void comboBoxLoad(Ui::PurchaseHistory* ui);


PurchaseHistory::PurchaseHistory(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PurchaseHistory)
{
    ui->setupUi(this);

    showReport(ui);
    comboBoxLoad(ui);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

PurchaseHistory::~PurchaseHistory()
{
    delete ui;
}



void comboBoxLoad(Ui::PurchaseHistory* ui)
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {

        QString querystring = "SELECT Name FROM Cities WHERE IsActive=1";

        QSqlQuery modelquery;

        modelquery.exec(querystring);
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(modelquery);
        //model->setHeaderData(0, Qt::Horizontal, "ID");
        model->setHeaderData(0, Qt::Horizontal, "City Name");


        ui->comboBox->setModel(model);


        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}





void showReport(Ui::PurchaseHistory* ui)
{
    QMessageBox msgBox;


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
            //===================================================

            QStandardItemModel *model = new QStandardItemModel(0,6);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("City Name"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Food Name"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantity"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Totoal Price"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Total Of All Purchases"));

            ui->tableView->setModel(model);
            ui->tableView->show();

            int row = 0, column = 0;
            double totalPurchases=0;
            QSqlQuery query;
            query.exec("SELECT City_Name, Food_Name, Price, Quantity, Total_Price FROM Purchase_History");
            while(query.next())
            {
                query.value(0).toString();
                query.value(1).toString();
                query.value(2).toString();
                query.value(3).toString();
                query.value(4).toString();
                totalPurchases += query.value(4).toDouble();

                QStandardItem *item0 = new QStandardItem(query.value(0).toString());
                model->setItem(row,column++,item0);

                QStandardItem *item1 = new QStandardItem(query.value(1).toString());
                model->setItem(row,column++,item1);

                QStandardItem *item2 = new QStandardItem(query.value(2).toString());
                model->setItem(row,column++,item2);

                QStandardItem *item3 = new QStandardItem(query.value(3).toString());
                model->setItem(row,column++,item3);


                QStandardItem *item4 = new QStandardItem(query.value(4).toString());
                model->setItem(row,column++,item4);


               row++;
               column=0;
            }

            QStandardItem *item5 = new QStandardItem(QString(QString::number(totalPurchases)));
            model->setItem(row,5,item5);
            ui->tableView->update();



        /*

        QSqlQueryModel* queryModel= new QSqlQueryModel;

        queryModel->setQuery("SELECT City_Name, Food_Name, Price, Quantity, Total_Price FROM Purchase_History");
        queryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("City Name"));
        queryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Food Name"));
        queryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
         queryModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantity"));
          queryModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Totoal Price"));
          //queryModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Sum Of "));
        ui->tableView->setModel(queryModel);
        ui->tableView->show();
        //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
*/

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }

}




void PurchaseHistory::on_pushButton_selectCity_clicked()
{
    // Search based on a city button

    QString cityName= ui->comboBox->currentText();

    QMessageBox msgBox;


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {

        //===================================================

        QStandardItemModel *model = new QStandardItemModel(0,6);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("City Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Food Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantity"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Totoal Price"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Total Of All Purchases"));

        ui->tableView->setModel(model);
        ui->tableView->show();

        int row = 0, column = 0;
        double totalPurchases=0;
        QSqlQuery query;
        query.exec("SELECT City_Name, Food_Name, Price, Quantity, Total_Price FROM Purchase_History WHERE City_Name LIKE '%"+cityName+"%'");
        while(query.next())
        {
            query.value(0).toString();
            query.value(1).toString();
            query.value(2).toString();
            query.value(3).toString();
            query.value(4).toString();
            totalPurchases += query.value(4).toDouble();

            QStandardItem *item0 = new QStandardItem(query.value(0).toString());
            model->setItem(row,column++,item0);

            QStandardItem *item1 = new QStandardItem(query.value(1).toString());
            model->setItem(row,column++,item1);

            QStandardItem *item2 = new QStandardItem(query.value(2).toString());
            model->setItem(row,column++,item2);

            QStandardItem *item3 = new QStandardItem(query.value(3).toString());
            model->setItem(row,column++,item3);


            QStandardItem *item4 = new QStandardItem(query.value(4).toString());
            model->setItem(row,column++,item4);


           row++;
           column=0;
        }

        QStandardItem *item5 = new QStandardItem(QString(QString::number(totalPurchases)));
        model->setItem(row,5,item5);
        ui->tableView->update();

        //==================================================


/*

        QSqlQueryModel* queryModel= new QSqlQueryModel();

        queryModel->setQuery("SELECT City_Name, Food_Name, Price, Quantity, Total_Price FROM Purchase_History WHERE City_Name LIKE '%"+cityName+"%'");
        queryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("City Name"));
        queryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Food Name"));
        queryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
         queryModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantity"));
          queryModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Totoal Price"));
          queryModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Total Of All Purchases"));
        ui->tableView->setModel(queryModel);
        ui->tableView->show();

*/
        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }

}

