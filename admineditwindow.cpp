#include "admineditwindow.h"
#include "ui_admineditwindow.h"
#include "dbhandler.h"


void comboBoxLoad(Ui::AdminEditWindow* ui);

QString deleteFoodItem[3]={""};
QString deleteDistancesItem[3]={""};

AdminEditWindow::AdminEditWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminEditWindow)
{
    ui->setupUi(this);
    comboBoxLoad(ui);
    ui->tableWidget_delete_food->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_delete_distances->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

AdminEditWindow::~AdminEditWindow()
{
    delete ui;
}






void comboBoxLoad(Ui::AdminEditWindow* ui)
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
         ui->comboBoxDeleteFoodCities->addItem("Choose a city");

        QSqlQuery query;
        query.exec("SELECT Name FROM Cities WHERE IsActive=1");
        while(query.next())
        {
            ui->comboBoxDeleteCity->addItem(query.value(0).toString());
            ui->comboBoxNewFoodCities->addItem(query.value(0).toString());
            ui->comboBoxDeleteFoodCities->addItem(query.value(0).toString());
            ui->comboBoxStartingCityADD->addItem(query.value(0).toString());
            ui->comboBoxEndingCityADD->addItem(query.value(0).toString());
            ui->comboBoxDeleteDistances->addItem(query.value(0).toString());
        }


       /* QString querystring = "SELECT Name FROM Cities WHERE IsActive=1";

        QSqlQuery modelquery;

        modelquery.exec(querystring);
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(modelquery);
        //model->setHeaderData(0, Qt::Horizontal, "ID");
        model->setHeaderData(0, Qt::Horizontal, "City Name");


        ui->comboBoxStartCity->setModel(model);*/

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}








void AdminEditWindow::on_add_city_button_clicked()
{
    QString newCity = ui->textEdit_add_new_City->toPlainText();


    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO Cities (Name) VALUES('" + newCity + "')");
        if(query.exec())
        {
            msgBox.setText("Success!");
            msgBox.exec();
        }

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }

}





void AdminEditWindow::on_delete_city_button_clicked()
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QString deleteCity = ui->comboBoxDeleteCity->currentText();
        QSqlQuery query;
        query.prepare("DELETE FROM Cities WHERE Name = '" + deleteCity + "'");
        if(query.exec())
        {
            msgBox.setText("Success!");
            msgBox.exec();
        }

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}





void AdminEditWindow::on_add_city_button_2_clicked()
{
    // not working!!!!1

}


void AdminEditWindow::on_add_food_button_clicked()
{
    QString newFood = ui->textEdit_add_new_food->toPlainText();
    QString newFoodPrice = ui->textEdit_add_new_food_price->toPlainText();
    QString city = ui->comboBoxNewFoodCities->currentText();

    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO Foods (City,Food,Price) VALUES('" + city + "','" + newFood + "','" + newFoodPrice + "')");
        if(query.exec())
        {
            msgBox.setText("Success!");
            msgBox.exec();
        }

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}






void AdminEditWindow::on_delete_food_button_clicked()
{

    if(deleteFoodItem[2]!="")
    {
        QMessageBox msgBox;

        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QString deleteCity = ui->comboBoxDeleteFoodCities->currentText(); // are same thing deleteFoodItem[0]
            QSqlQuery query;
            query.prepare("DELETE FROM Foods WHERE City = '" + deleteFoodItem[0] + "' AND Food LIKE '%"+deleteFoodItem[1]+"%'");
            if(query.exec())
            {
                msgBox.setText("Success!");
                msgBox.exec();
            }

            dbHandler.close();
        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
        }
    }

}


void AdminEditWindow::on_comboBoxDeleteFoodCities_currentIndexChanged(int index)
{

    if(ui->comboBoxDeleteFoodCities->currentIndex()!=0)
    {
        QString city = ui->comboBoxDeleteFoodCities->currentText();
        ui->tableWidget_delete_food->clearContents();

        QMessageBox msgBox;

        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            ui->tableWidget_delete_food->setColumnCount(3);
            ui->tableWidget_delete_food->setRowCount(20);
            QStringList labels = {"City","Food","Price"};
            ui->tableWidget_delete_food->setHorizontalHeaderLabels(labels);



             QSqlQuery query;
             int row = 0;
             int column = 0;

             //ui->tableWidget_delete_food->setColumnCount(3);
            // ui->tableWidget_delete_food->setRowCount(20);
             //QStringList labels = {"City","Food","Price"};
            // ui->tableWidget_delete_food->setHorizontalHeaderLabels(labels);

             query.exec("SELECT City, Food, Price FROM Foods WHERE City LIKE '%"+city+"%' AND IsActive=1");

             while(query.next())
             {
                 ui->tableWidget_delete_food->setItem(row,column++,new QTableWidgetItem(query.value(0).toString()));
                 ui->tableWidget_delete_food->setItem(row,column++,new QTableWidgetItem(query.value(1).toString()));
                 ui->tableWidget_delete_food->setItem(row,column++,new QTableWidgetItem(query.value(2).toString()));
                  column = 0;
                  row++;
             }
             ui->tableWidget_delete_food->update();
             ui->tableWidget_delete_food->show();

            dbHandler.close();
        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
        }

    }

    else
    {
        ui->tableWidget_delete_food->setColumnCount(3);
        ui->tableWidget_delete_food->setRowCount(20);
        QStringList labels = {"City","Food","Price"};
        ui->tableWidget_delete_food->setHorizontalHeaderLabels(labels);
        ui->tableWidget_delete_food->update();
        ui->tableWidget_delete_food->show();
        ui->tableWidget_delete_food->clearContents();


    }

}


void AdminEditWindow::on_comboBoxDeleteFoodCities_currentTextChanged(const QString &arg1)
{

}

void AdminEditWindow::on_tableWidget_delete_food_cellDoubleClicked(int row, int column)
{
    //QMessageBox msgBox;

    if(deleteFoodItem[2]=="")
    {
        deleteFoodItem[0]=ui->tableWidget_delete_food->item(row,0)->text();//city
        deleteFoodItem[1]=ui->tableWidget_delete_food->item(row,1)->text();//food
        deleteFoodItem[2]=QString::number(row);//row

        ui->tableWidget_delete_food->item(row,0)->setBackground(QBrush(Qt::red));
        ui->tableWidget_delete_food->item(row,1)->setBackground(QBrush(Qt::red));
        ui->tableWidget_delete_food->item(row,2)->setBackground(QBrush(Qt::red));
    }
    else
    {
        ui->tableWidget_delete_food->item(deleteFoodItem[2].toInt(),0)->setBackground(QBrush(Qt::transparent));
        ui->tableWidget_delete_food->item(deleteFoodItem[2].toInt(),1)->setBackground(QBrush(Qt::transparent));
        ui->tableWidget_delete_food->item(deleteFoodItem[2].toInt(),2)->setBackground(QBrush(Qt::transparent));



        deleteFoodItem[0]=ui->tableWidget_delete_food->item(row,0)->text();//city
        deleteFoodItem[1]=ui->tableWidget_delete_food->item(row,1)->text();//food
        deleteFoodItem[2]=QString::number(row);//row

        ui->tableWidget_delete_food->item(row,0)->setBackground(QBrush(Qt::red));
        ui->tableWidget_delete_food->item(row,1)->setBackground(QBrush(Qt::red));
        ui->tableWidget_delete_food->item(row,2)->setBackground(QBrush(Qt::red));
    }


    //msgBox.setText(deleteFoodItem[0]+"  "+deleteFoodItem[1]);
    //msgBox.exec();
}







void AdminEditWindow::on_add_distance_button__clicked()
{
    QMessageBox msgBox;
    QString startingCity = ui->comboBoxStartingCityADD->currentText();
    QString endingCity = ui->comboBoxEndingCityADD->currentText();

    QString kilometer = ui->textEdit_add_new_Kilometers->toPlainText();


    if(startingCity!=endingCity && kilometer!="")
    {
        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {

            QSqlQuery query;
            query.prepare("INSERT INTO Distances (Starting_City_Name,Ending_City_Name,Kilometers) VALUES('" + startingCity + "','" + endingCity + "','" + kilometer + "')");
            if(query.exec())
            {
                msgBox.setText("Success!");
                msgBox.exec();
            }

            dbHandler.close();
        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
        }
    }
    else
    {
        msgBox.setText("One city must be different or enter kilometers!!");
        msgBox.exec();
    }

}







void AdminEditWindow::on_comboBoxDeleteDistances_currentIndexChanged(int index)
{
    if(ui->comboBoxDeleteDistances->currentIndex()!=0)
    {
        QString city = ui->comboBoxDeleteDistances->currentText();
        ui->tableWidget_delete_distances->clearContents();

        QMessageBox msgBox;

        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            ui->tableWidget_delete_distances->setColumnCount(3);
            ui->tableWidget_delete_distances->setRowCount(20);
            QStringList labels = {"Starting City","Ending City","Kilometers"};
            ui->tableWidget_delete_distances->setHorizontalHeaderLabels(labels);



             QSqlQuery query;
             int row = 0;
             int column = 0;

             //ui->tableWidget_delete_food->setColumnCount(3);
            // ui->tableWidget_delete_food->setRowCount(20);
             //QStringList labels = {"City","Food","Price"};
            // ui->tableWidget_delete_food->setHorizontalHeaderLabels(labels);

             query.exec("SELECT Starting_City_Name, Ending_City_Name, Kilometers FROM Distances WHERE Starting_City_Name LIKE '%"+city+"%' AND IsActive=1");

             while(query.next())
             {
                 ui->tableWidget_delete_distances->setItem(row,column++,new QTableWidgetItem(query.value(0).toString()));
                 ui->tableWidget_delete_distances->setItem(row,column++,new QTableWidgetItem(query.value(1).toString()));
                 ui->tableWidget_delete_distances->setItem(row,column++,new QTableWidgetItem(query.value(2).toString()));
                  column = 0;
                  row++;
             }
             ui->tableWidget_delete_distances->update();
             ui->tableWidget_delete_distances->show();

            dbHandler.close();
        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
        }

    }

    else
    {
        ui->tableWidget_delete_distances->setColumnCount(3);
        ui->tableWidget_delete_distances->setRowCount(20);
        QStringList labels = {"Starting City","Ending City","Kilometers"};
        ui->tableWidget_delete_distances->setHorizontalHeaderLabels(labels);
        ui->tableWidget_delete_distances->update();
        ui->tableWidget_delete_distances->show();
        ui->tableWidget_delete_distances->clearContents();


    }

}


void AdminEditWindow::on_tableWidget_delete_distances_cellDoubleClicked(int row, int column)
{

    if(deleteDistancesItem[2]=="")
    {
        deleteDistancesItem[0]=ui->tableWidget_delete_distances->item(row,0)->text();//city
        deleteDistancesItem[1]=ui->tableWidget_delete_distances->item(row,1)->text();//food
        deleteDistancesItem[2]=QString::number(row);//row

        ui->tableWidget_delete_distances->item(row,0)->setBackground(QBrush(Qt::red));
        ui->tableWidget_delete_distances->item(row,1)->setBackground(QBrush(Qt::red));
        ui->tableWidget_delete_distances->item(row,2)->setBackground(QBrush(Qt::red));
    }
    else
    {
        ui->tableWidget_delete_distances->item(deleteDistancesItem[2].toInt(),0)->setBackground(QBrush(Qt::transparent));
        ui->tableWidget_delete_distances->item(deleteDistancesItem[2].toInt(),1)->setBackground(QBrush(Qt::transparent));
        ui->tableWidget_delete_distances->item(deleteDistancesItem[2].toInt(),2)->setBackground(QBrush(Qt::transparent));



        deleteDistancesItem[0]=ui->tableWidget_delete_distances->item(row,0)->text();//city
        deleteDistancesItem[1]=ui->tableWidget_delete_distances->item(row,1)->text();//food
        deleteDistancesItem[2]=QString::number(row);//row

        ui->tableWidget_delete_distances->item(row,0)->setBackground(QBrush(Qt::red));
        ui->tableWidget_delete_distances->item(row,1)->setBackground(QBrush(Qt::red));
        ui->tableWidget_delete_distances->item(row,2)->setBackground(QBrush(Qt::red));
    }


}


void AdminEditWindow::on_delete_distances_button_clicked()
{
    if(deleteDistancesItem[2]!="")
    {
        QMessageBox msgBox;

        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QString deleteCity = ui->comboBoxDeleteDistances->currentText(); // are same thing deleteDistancesItem[0]
            QSqlQuery query;
            query.prepare("DELETE FROM Distances WHERE Starting_City_Name = '" + deleteDistancesItem[0] + "' AND Ending_City_Name LIKE '%"+deleteDistancesItem[1]+"%'");
            if(query.exec())
            {
                msgBox.setText("Success!");
                msgBox.exec();
            }

            dbHandler.close();
        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
        }
    }
}

