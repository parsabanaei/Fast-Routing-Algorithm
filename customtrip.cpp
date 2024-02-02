#include "customtrip.h"
#include "QtWidgets/qtablewidget.h"
#include "ui_customtrip.h"
#include "purchaseform.h"
#include "dbhandler.h"
#include <QVector>

void comboBoxLoad(Ui::CustomTrip* ui);

QVector<QString> vecCities;
QVector<QString> vecFavCities;
int countOfCities;

int min_Function(double arr[], int size, int *index);
void travel_Efficiently(Ui::CustomTrip* ui,QStandardItemModel *model, QString city,QVector<QString> otherCities,int row, int column,double total_kilometers);

CustomTrip::CustomTrip(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomTrip)
{
    ui->setupUi(this);


    countOfCities = 0;
    comboBoxLoad(ui);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


}

CustomTrip::~CustomTrip()
{
    delete ui;
}



void comboBoxLoad(Ui::CustomTrip* ui)
{
    ui->comboBoxStartCity->addItem("choose a city");
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {

        QSqlQuery query;
        query.exec("SELECT Name FROM Cities WHERE IsActive=1");
        while(query.next())
        {
            countOfCities+=1;
            vecCities.push_back(query.value(0).toString());
            ui->comboBoxStartCity->addItem(query.value(0).toString());
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





void CustomTrip::on_comboBoxStartCity_currentIndexChanged(int index)
{
    // comboBox: starting city changed
      vecFavCities.clear();

    if(ui->comboBoxStartCity->currentIndex()!=0)
    {
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setRowCount(20);
        QStringList labels = {"City Name"};
        ui->tableWidget->setHorizontalHeaderLabels(labels);

        int row=0;
        int counter = countOfCities;
        int i=0;
        QString selectedCity = ui->comboBoxStartCity->currentText();
        while(counter>0)
            {
                if(selectedCity!=vecCities[i])
                    {
                        ui->tableWidget->setItem(row,0,new QTableWidgetItem(vecCities[i]));
                        row++;
                    }
                i++;
                counter--;
            }
        ui->tableWidget->setRowCount(row);
        ui->tableWidget->update();
        ui->tableWidget->show();
    }
    else
    {
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setRowCount(0);
        QStringList labels = {"City Name"};
        ui->tableWidget->setHorizontalHeaderLabels(labels);
        ui->tableWidget->update();
        ui->tableWidget->show();

    }



}





void CustomTrip::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString str = ui->tableWidget->item(row,column)->text();
    bool flag = true;

    if(vecFavCities.length()<1)
    {
        vecFavCities.push_back(str);
        ui->tableWidget->item(row,column)->setBackground(QBrush(Qt::green));
    }
    else
    {
        for(int i=0;i<vecFavCities.length();i++)
        {
            if(str==vecFavCities[i])
            {
                // remove the item and green color
                vecFavCities.remove(i);
                ui->tableWidget->item(row,column)->setBackground(QBrush(Qt::transparent));
                flag = false;
                break;
            }
        }

        if(flag)
        {
            // add new item and green color

            vecFavCities.push_back(str);
            ui->tableWidget->item(row,column)->setBackground(QBrush(Qt::green));
        }
    }


}





void CustomTrip::on_pushButton_travel_efficiently_clicked()
{
    // Travel Efficiently (recursively choose the city closest to the previous city)

    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        if(!vecFavCities.empty())
        {
        QStandardItemModel *model = new QStandardItemModel(0,4);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Starting City"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ending City"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Kilometers"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Total Distance"));

        ui->tableView->setModel(model);
        ui->tableView->show();


        QString startCity= ui->comboBoxStartCity->currentText();


        double total_kilometers=0;


        travel_Efficiently(ui, model, startCity, vecFavCities, 0, 0, total_kilometers);
        }
        else
        {
            msgBox.setText("Choose you favorite cities");
            msgBox.exec();
        }

    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}





void travel_Efficiently(Ui::CustomTrip* ui,QStandardItemModel *model,  QString city, QVector<QString> otherCities,int row, int column,double total_kilometers)
{
    int vectorSize = otherCities.length();
    QSqlQuery query;
    QString Ending_City_Names[vectorSize];
    double Kilometers[vectorSize];
    int index = 0;
    QString min_city;
    double min_kilometer;



    for(int i = 0 ; i < vectorSize ; i++)
    {
        QString endingCity=otherCities[i];

        query.exec("SELECT Ending_City_Name, Kilometers FROM Distances WHERE Starting_City_Name LIKE '%"+city+"%' AND Ending_City_Name LIKE '%"+endingCity+"%' AND IsActive=1");

        while(query.next()) // will return only one record
        {
            Ending_City_Names[index] = query.value(0).toString();
            Kilometers[index++] = query.value(1).toDouble();
        }
    }

    int city_index=0; // respective city name index will be returned from function into the pointer
    int arrSize = sizeof(Kilometers)/sizeof(Kilometers[0]);;
    min_kilometer = min_Function(Kilometers,arrSize,&city_index);
    min_city = Ending_City_Names[city_index]; // next starting city



    QStandardItem *item0 = new QStandardItem(QString(city));
    model->setItem(row,column++,item0);

    QStandardItem *item1 = new QStandardItem(QString(min_city));
    model->setItem(row,column++,item1);

    QStandardItem *item2 = new QStandardItem(QString(QString::number(min_kilometer)));
    model->setItem(row,column++,item2);
    total_kilometers+=min_kilometer;

   ui->tableView->update();
   row++;
   column=0;



       //QVector<QString>::iterator it;
       for (auto it = otherCities.begin(); it < otherCities.end(); ++it)
       {
           if(*it==min_city)
           {
               otherCities.erase(it);
           }

       }


    /*for(int i=0;i<vectorSize;i++)
    {
        if(otherCities[i]==min_city)
        {

            otherCities.removeAt(i);
        }

    }*/

    if(vectorSize > 1)
        travel_Efficiently(ui, model, min_city,otherCities, row, column,total_kilometers);
    else
        {
            QStandardItem *item2 = new QStandardItem(QString(QString::number(total_kilometers)+" Kilometers"));
            model->setItem(--row,3,item2);
            ui->tableView->update();
        }


}




int min_Function(double arr[], int size, int *index)
{
    // part number 3
    int min;

    for(int i = 0 ; i < size ; i++)
    {
        if(i==0)
        {
            min = arr[i];
            *index = i;
        }

        else
        {
            if(min > arr[i])
            {
                min = arr[i];
                *index = i;
            }
        }
    }

    return min;
}



void CustomTrip::on_tableView_doubleClicked(const QModelIndex &index)
{
    // handle double click on each cell to pull up the food items
    QMessageBox msgBox;
    if(index.column()==0 || index.column()==1)
    {
        QString selectedCity= index.data().toString();

        PurchaseForm *form;
        //hide();
        form = new PurchaseForm(selectedCity,this);
        form->show();
    }
}

