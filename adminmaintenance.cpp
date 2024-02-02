#include "adminmaintenance.h"
#include "ui_adminmaintenance.h"
#include "dbhandler.h"

void addComboBoxLoad(Ui::AdminMaintenance* ui);
void removeComboBoxLoad(Ui::AdminMaintenance* ui);
void removeFoodTableLoad(Ui::AdminMaintenance* ui);
void addFoodTableLoad(Ui::AdminMaintenance* ui);
QString updateFoodItem[4]={""};
QString removeFoodItem[4]={""};
QString addFoodItem[4]={""};
int rowCounter = 0;


AdminMaintenance::AdminMaintenance(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMaintenance)
{
    ui->setupUi(this);

    addComboBoxLoad(ui);
    removeComboBoxLoad(ui);
    removeFoodTableLoad(ui);
    addFoodTableLoad(ui);
    ui->tableWidget_update_food->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_remove_food->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_add_food->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

AdminMaintenance::~AdminMaintenance()
{
    delete ui;
}


//=====================================ADD CITY===============================================
void addComboBoxLoad(Ui::AdminMaintenance* ui)
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
         ui->comboBoxAddNewCity->addItem("Choose a city");

        QSqlQuery query;
        query.exec("SELECT Name FROM Cities WHERE IsActive=0");
        while(query.next())
        {
            ui->comboBoxAddNewCity->addItem(query.value(0).toString());
        }

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}


void AdminMaintenance::on_add_city_button_clicked()
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {

        if(ui->comboBoxAddNewCity->currentIndex()!=0)
        {
            QString IsActive = "1";
            QString newCity = ui->comboBoxAddNewCity->currentText();
            QSqlQuery qry;
            qry.prepare("UPDATE Cities set IsActive=? WHERE Name LIKE '%"+newCity+"%'");

            qry.addBindValue(IsActive);

            if(qry.exec())
            {
                QSqlQuery qry2;
                qry2.prepare("UPDATE Foods set IsActive=? WHERE City LIKE '%"+newCity+"%'");
                qry2.addBindValue(IsActive);

                if(qry2.exec())
                {
                    QSqlQuery qry3;
                    qry3.prepare("UPDATE Distances set IsActive=? WHERE Starting_City_Name LIKE '%"+newCity+"%' OR Ending_City_Name LIKE '%"+newCity+"%'");
                    qry3.addBindValue(IsActive);

                     if(qry3.exec())
                     {
                         msgBox.setText("Success!");
                         msgBox.exec();
                     }


                }


            }
        }

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}





//==================================REMOVE CITY==================================================
void removeComboBoxLoad(Ui::AdminMaintenance* ui)
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
         ui->comboBoxRemoveCity->addItem("Choose a city");
         ui->comboBoxUpdateFoods->addItem("Choose a city");

        QSqlQuery query;
        query.exec("SELECT Name FROM Cities WHERE IsActive=1");
        while(query.next())
        {
            ui->comboBoxRemoveCity->addItem(query.value(0).toString());
            ui->comboBoxUpdateFoods->addItem(query.value(0).toString());
        }

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}


void AdminMaintenance::on_remove_city_button_clicked()
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {

        if(ui->comboBoxRemoveCity->currentIndex()!=0)
        {
            QString IsActive = "0";
            QString newCity = ui->comboBoxRemoveCity->currentText();
            QSqlQuery qry;
            qry.prepare("UPDATE Cities set IsActive=? WHERE Name LIKE '%"+newCity+"%'");

            qry.addBindValue(IsActive);

            if(qry.exec())
            {
                QSqlQuery qry2;
                qry2.prepare("UPDATE Foods set IsActive=? WHERE City LIKE '%"+newCity+"%'");
                qry2.addBindValue(IsActive);

                if(qry2.exec())
                {
                    QSqlQuery qry3;
                    qry3.prepare("UPDATE Distances set IsActive=? WHERE Starting_City_Name LIKE '%"+newCity+"%' OR Ending_City_Name LIKE '%"+newCity+"%'");
                    qry3.addBindValue(IsActive);

                     if(qry3.exec())
                     {
                         msgBox.setText("Success!");
                         msgBox.exec();
                     }


                }


            }
        }

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}





//======================================UPDATE FOOD PRICE==============================================
void AdminMaintenance::on_update_food_button_clicked()
{
    QMessageBox msgBox;

    if(updateFoodItem[0]!="" &&  ui->textEdit_update_food_price->toPlainText()!="")
    {
        QString price = ui->textEdit_update_food_price->toPlainText();



        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {

            QSqlQuery qry;
            qry.prepare("UPDATE Foods set Price=? WHERE City LIKE '%"+updateFoodItem[0]+"%' AND Food LIKE '%"+updateFoodItem[1]+"%'");

            qry.addBindValue(price);

            if(qry.exec())
            {
                msgBox.setText("Success!");
                msgBox.exec();
            }


            ui->tableWidget_update_food->item(updateFoodItem[3].toInt(),0)->setBackground(QBrush(Qt::green));
            ui->tableWidget_update_food->item(updateFoodItem[3].toInt(),1)->setBackground(QBrush(Qt::green));
            ui->tableWidget_update_food->item(updateFoodItem[3].toInt(),2)->setBackground(QBrush(Qt::green));

            updateFoodItem[0]="";
            updateFoodItem[1]="";
            updateFoodItem[2]="";
            updateFoodItem[3]="";

            dbHandler.close();
        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
        }


    }

}


void AdminMaintenance::on_comboBoxUpdateFoods_currentIndexChanged(int index)
{

    if(ui->comboBoxUpdateFoods->currentIndex()!=0)
    {
        rowCounter=0;

        QString city = ui->comboBoxUpdateFoods->currentText();
        ui->tableWidget_update_food->clearContents();

        QMessageBox msgBox;

        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            ui->tableWidget_update_food->setColumnCount(3);
            ui->tableWidget_update_food->setRowCount(20);
            QStringList labels = {"City","Food","Price"};
            ui->tableWidget_update_food->setHorizontalHeaderLabels(labels);



             QSqlQuery query;
             int row = 0;
             int column = 0;


             query.exec("SELECT City, Food, Price FROM Foods WHERE City LIKE '%"+city+"%' AND IsActive=1");

             while(query.next())
             {
                 rowCounter += 1;
                 ui->tableWidget_update_food->setItem(row,column++,new QTableWidgetItem(query.value(0).toString()));
                 ui->tableWidget_update_food->setItem(row,column++,new QTableWidgetItem(query.value(1).toString()));
                 ui->tableWidget_update_food->setItem(row,column++,new QTableWidgetItem(query.value(2).toString()));
                  column = 0;
                  row++;
             }
             ui->tableWidget_update_food->setRowCount(rowCounter);
             ui->tableWidget_update_food->update();
             ui->tableWidget_update_food->show();

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
        rowCounter = 0;
        ui->tableWidget_update_food->setColumnCount(3);
        ui->tableWidget_update_food->setRowCount(20);
        QStringList labels = {"City","Food","Price"};
        ui->tableWidget_update_food->setHorizontalHeaderLabels(labels);
        ui->tableWidget_update_food->update();
        ui->tableWidget_update_food->show();
        ui->tableWidget_update_food->clearContents();


    }

    ui->textEdit_update_food_price->setPlainText("");
    updateFoodItem[0]="";
    updateFoodItem[1]="";
    updateFoodItem[2]="";
    updateFoodItem[3]="";
}


void AdminMaintenance::on_tableWidget_update_food_cellDoubleClicked(int row, int column)
{
    if(updateFoodItem[2]=="" && ui->comboBoxUpdateFoods->currentIndex()!=0)
    {
        updateFoodItem[0]=ui->tableWidget_update_food->item(row,0)->text();//city
        updateFoodItem[1]=ui->tableWidget_update_food->item(row,1)->text();//food
        updateFoodItem[2]=ui->tableWidget_update_food->item(row,2)->text();//price that has to be changed
        updateFoodItem[3]=QString::number(row);//row

        ui->tableWidget_update_food->item(row,0)->setBackground(QBrush(Qt::red));
        ui->tableWidget_update_food->item(row,1)->setBackground(QBrush(Qt::red));
        ui->tableWidget_update_food->item(row,2)->setBackground(QBrush(Qt::red));
        ui->textEdit_update_food_price->setPlainText(updateFoodItem[2]);
    }
    else if(ui->comboBoxUpdateFoods->currentIndex()!=0)
    {
        ui->tableWidget_update_food->item(updateFoodItem[3].toInt(),0)->setBackground(QBrush(Qt::transparent));
        ui->tableWidget_update_food->item(updateFoodItem[3].toInt(),1)->setBackground(QBrush(Qt::transparent));
        ui->tableWidget_update_food->item(updateFoodItem[3].toInt(),2)->setBackground(QBrush(Qt::transparent));



        updateFoodItem[0]=ui->tableWidget_update_food->item(row,0)->text();//city
        updateFoodItem[1]=ui->tableWidget_update_food->item(row,1)->text();//food
        updateFoodItem[2]=ui->tableWidget_update_food->item(row,2)->text();//price that has to be changed
        updateFoodItem[3]=QString::number(row);//row

        ui->tableWidget_update_food->item(row,0)->setBackground(QBrush(Qt::red));
        ui->tableWidget_update_food->item(row,1)->setBackground(QBrush(Qt::red));
        ui->tableWidget_update_food->item(row,2)->setBackground(QBrush(Qt::red));

        ui->textEdit_update_food_price->setPlainText(updateFoodItem[2]);
    }


}





//=====================================REMOVE FOOD===============================================
void AdminMaintenance::on_remove_food_button_clicked()
{
    QMessageBox msgBox;

    if(removeFoodItem[2]!="")
    {

        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QString IsActive = "0";
            QSqlQuery qry1;
            qry1.prepare("UPDATE Foods set IsFoodActive=? WHERE City LIKE '%"+removeFoodItem[0]+"%' AND Food LIKE '%"+removeFoodItem[1]+"%'");

            qry1.addBindValue(IsActive);

            if(qry1.exec())
            {
                msgBox.setText("Success!");
                msgBox.exec();
            }


            ui->tableWidget_remove_food->item(removeFoodItem[3].toInt(),0)->setBackground(QBrush(Qt::green));
            ui->tableWidget_remove_food->item(removeFoodItem[3].toInt(),1)->setBackground(QBrush(Qt::green));
            ui->tableWidget_remove_food->item(removeFoodItem[3].toInt(),2)->setBackground(QBrush(Qt::green));

            removeFoodItem[0]="";
            removeFoodItem[1]="";
            removeFoodItem[2]="";
            removeFoodItem[3]="";


            dbHandler.close();
        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
        }


    }


}


void removeFoodTableLoad(Ui::AdminMaintenance* ui)
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        ui->tableWidget_remove_food->clearContents();

        ui->tableWidget_remove_food->setColumnCount(3);
        ui->tableWidget_remove_food->setRowCount(50);
        QStringList labels = {"City","Food","Price"};
        ui->tableWidget_remove_food->setHorizontalHeaderLabels(labels);



        QSqlQuery query;
        int row = 0;
        int column = 0;

        query.exec("SELECT City, Food, Price FROM Foods WHERE IsActive=1 AND IsFoodActive=1");
        while(query.next())
        {
            ui->tableWidget_remove_food->setItem(row,column++,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget_remove_food->setItem(row,column++,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget_remove_food->setItem(row,column++,new QTableWidgetItem(query.value(2).toString()));
            column = 0;
             row++;
        }
        ui->tableWidget_remove_food->setRowCount(row);
        ui->tableWidget_remove_food->update();
        ui->tableWidget_remove_food->show();

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}


void AdminMaintenance::on_tableWidget_remove_food_cellDoubleClicked(int row, int column)
{



    if(removeFoodItem[2]=="")
    {
        removeFoodItem[0]=ui->tableWidget_remove_food->item(row,0)->text();//city
        removeFoodItem[1]=ui->tableWidget_remove_food->item(row,1)->text();//food
        removeFoodItem[2]=ui->tableWidget_remove_food->item(row,2)->text();//price that has to be changed
        removeFoodItem[3]=QString::number(row);//row

        ui->tableWidget_remove_food->item(row,0)->setBackground(QBrush(Qt::red));
        ui->tableWidget_remove_food->item(row,1)->setBackground(QBrush(Qt::red));
        ui->tableWidget_remove_food->item(row,2)->setBackground(QBrush(Qt::red));

    }
    else
    {
        ui->tableWidget_remove_food->item(removeFoodItem[3].toInt(),0)->setBackground(QBrush(Qt::transparent));
        ui->tableWidget_remove_food->item(removeFoodItem[3].toInt(),1)->setBackground(QBrush(Qt::transparent));
        ui->tableWidget_remove_food->item(removeFoodItem[3].toInt(),2)->setBackground(QBrush(Qt::transparent));



        removeFoodItem[0]=ui->tableWidget_remove_food->item(row,0)->text();//city
        removeFoodItem[1]=ui->tableWidget_remove_food->item(row,1)->text();//food
        removeFoodItem[2]=ui->tableWidget_remove_food->item(row,2)->text();//price that has to be changed
        removeFoodItem[3]=QString::number(row);//row

        ui->tableWidget_remove_food->item(row,0)->setBackground(QBrush(Qt::red));
        ui->tableWidget_remove_food->item(row,1)->setBackground(QBrush(Qt::red));
        ui->tableWidget_remove_food->item(row,2)->setBackground(QBrush(Qt::red));


    }




}





//========================================ADD FOOD============================================
void AdminMaintenance::on_add_food_button_clicked()
{
    QMessageBox msgBox;

    if(addFoodItem[2]!="")
    {

        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QString IsActive = "1";
            QSqlQuery qry1;
            qry1.prepare("UPDATE Foods set IsFoodActive=? WHERE City LIKE '%"+addFoodItem[0]+"%' AND Food LIKE '%"+addFoodItem[1]+"%'");

            qry1.addBindValue(IsActive);

            if(qry1.exec())
            {
                msgBox.setText("Success!");
                msgBox.exec();
            }


            ui->tableWidget_add_food->item(addFoodItem[3].toInt(),0)->setBackground(QBrush(Qt::green));
            ui->tableWidget_add_food->item(addFoodItem[3].toInt(),1)->setBackground(QBrush(Qt::green));
            ui->tableWidget_add_food->item(addFoodItem[3].toInt(),2)->setBackground(QBrush(Qt::green));

            addFoodItem[0]="";
            addFoodItem[1]="";
            addFoodItem[2]="";
            addFoodItem[3]="";


            dbHandler.close();
        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
        }

    }

}


void addFoodTableLoad(Ui::AdminMaintenance* ui)
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        ui->tableWidget_add_food->clearContents();

        ui->tableWidget_add_food->setColumnCount(3);
        ui->tableWidget_add_food->setRowCount(50);
        QStringList labels = {"City","Food","Price"};
        ui->tableWidget_add_food->setHorizontalHeaderLabels(labels);



        QSqlQuery query;
        int row = 0;
        int column = 0;

        query.exec("SELECT City, Food, Price FROM Foods WHERE IsActive=1 AND IsFoodActive=0");
        while(query.next())
        {
            ui->tableWidget_add_food->setItem(row,column++,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget_add_food->setItem(row,column++,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget_add_food->setItem(row,column++,new QTableWidgetItem(query.value(2).toString()));
            column = 0;
             row++;
        }
        ui->tableWidget_add_food->setRowCount(row);
        ui->tableWidget_add_food->update();
        ui->tableWidget_add_food->show();

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}


void AdminMaintenance::on_tableWidget_add_food_cellDoubleClicked(int row, int column)
{


    if(addFoodItem[2]=="")
    {
        addFoodItem[0]=ui->tableWidget_add_food->item(row,0)->text();//city
        addFoodItem[1]=ui->tableWidget_add_food->item(row,1)->text();//food
        addFoodItem[2]=ui->tableWidget_add_food->item(row,2)->text();//price that has to be changed
        addFoodItem[3]=QString::number(row);//row

        ui->tableWidget_add_food->item(row,0)->setBackground(QBrush(Qt::red));
        ui->tableWidget_add_food->item(row,1)->setBackground(QBrush(Qt::red));
        ui->tableWidget_add_food->item(row,2)->setBackground(QBrush(Qt::red));

    }
    else
    {
        ui->tableWidget_add_food->item(addFoodItem[3].toInt(),0)->setBackground(QBrush(Qt::transparent));
        ui->tableWidget_add_food->item(addFoodItem[3].toInt(),1)->setBackground(QBrush(Qt::transparent));
        ui->tableWidget_add_food->item(addFoodItem[3].toInt(),2)->setBackground(QBrush(Qt::transparent));



        addFoodItem[0]=ui->tableWidget_add_food->item(row,0)->text();//city
        addFoodItem[1]=ui->tableWidget_add_food->item(row,1)->text();//food
        addFoodItem[2]=ui->tableWidget_add_food->item(row,2)->text();//price that has to be changed
        addFoodItem[3]=QString::number(row);//row

        ui->tableWidget_add_food->item(row,0)->setBackground(QBrush(Qt::red));
        ui->tableWidget_add_food->item(row,1)->setBackground(QBrush(Qt::red));
        ui->tableWidget_add_food->item(row,2)->setBackground(QBrush(Qt::red));


    }
}





//========================================DELETE PURCHASE HISTORY============================================
void AdminMaintenance::on_delete_purchase_history_button_clicked()
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQuery query;
        query.prepare("DELETE FROM Purchase_History");
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




void AdminMaintenance::on_RefreshpushButton_clicked()
{
    this->close();
    AdminMaintenance *back = new AdminMaintenance(this);
    back->show();
}

