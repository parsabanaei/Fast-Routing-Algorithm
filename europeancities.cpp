#include "europeancities.h"
#include "ui_europeancities.h"
#include "dbhandler.h"
#include "purchaseform.h"

#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QVector>
#include "GlobalCitiesArray.h"

void showReport(Ui::EuropeanCities* ui);
void comboBoxLoad(Ui::EuropeanCities* ui);
//void getCitiesCount();
//int count_of_cities=0;

GlobalCities gc;
int minFunction(double arr[], int size, int *index);
void travelEfficiently(Ui::EuropeanCities* ui,QStandardItemModel *model, QString city,int count,QVector<QString> Prohibited_City_Names,int row, int column,double total_kilometers);

EuropeanCities::EuropeanCities(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EuropeanCities)
{
    ui->setupUi(this);

    gc.initial();//GlobalCitiesArray.h
   // getCitiesCount();
   //QString cities_Array[count_of_cities];



    ui->comboBox_2->addItem("Limit The Number Of Trips");
    int counter = gc.getCitiesCount()-1;
    while(counter>0)
    {
        ui->comboBox_2->addItem(QString::number(counter));
        counter--;
    }

    showReport(ui);
    comboBoxLoad(ui);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


EuropeanCities::~EuropeanCities()
{
    delete ui;
}


void showReport(Ui::EuropeanCities* ui)
{
    QMessageBox msgBox;


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQueryModel* queryModel= new QSqlQueryModel;

        queryModel->setQuery("SELECT Starting_City_Name, Ending_City_Name, Kilometers FROM Distances WHERE Starting_City_Name = 'Rome' AND IsActive=1");
        queryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Starting City Name"));
        queryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Ending City Name"));
        queryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Kilometers"));
        ui->tableView->setModel(queryModel);
        ui->tableView->show();
        //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }

}



void comboBoxLoad(Ui::EuropeanCities* ui)
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



void EuropeanCities::on_pushButton_clicked()
{
    //Search Based On Place Of Origin

    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQueryModel* queryModel= new QSqlQueryModel;

       QString city= ui->comboBox->currentText();

        queryModel->setQuery("SELECT Starting_City_Name, Ending_City_Name, Kilometers FROM Distances WHERE Starting_City_Name LIKE '%"+city+"%' AND IsActive=1");
        queryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Starting City Name"));
        queryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Ending City Name"));
        queryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Kilometers"));
        ui->tableView->setModel(queryModel);
        ui->tableView->show();
        //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}



void EuropeanCities::on_pushButton_2_clicked()
{
    // part number 3
    // Travel Efficiently (recursively choose the city closest to the previous city)

    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QStandardItemModel *model = new QStandardItemModel(0,4);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Starting City Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ending City Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Kilometers"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Total Distance Traveled"));

        ui->tableView->setModel(model);
        ui->tableView->show();


        QString city= ui->comboBox->currentText();

        QVector<QString> Prohibited_City_Names;
        double total_kilometers=0;
        int count;
        if(ui->comboBox_2->currentIndex()==0)
        {
            count = gc.getCitiesCount()-1;
        }
        else
        {
            count= ui->comboBox_2->currentText().toInt();
        }

        if(count <=gc.getCitiesCount() && count >=1)
        {
            travelEfficiently(ui,model,city,count,Prohibited_City_Names,0,0,total_kilometers);

        }
        else
        {
            travelEfficiently(ui,model,city,(gc.getCitiesCount()-1),Prohibited_City_Names,0,0,total_kilometers);
        }

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}



void travelEfficiently(Ui::EuropeanCities* ui,QStandardItemModel *model, QString city,int count,QVector<QString> Prohibited_City_Names,int row, int column,double total_kilometers)
{
    // part number 3
    QSqlQuery query;
    QString Ending_City_Names[gc.getCitiesCount()];
    double Kilometers[gc.getCitiesCount()];
    int index = 0;
    QString min_city;
    double min_kilometer;

    bool flag = true;
    int size = 0;


    query.exec("SELECT Ending_City_Name, Kilometers FROM Distances WHERE Starting_City_Name LIKE '%"+city+"%' AND IsActive=1");
                while(query.next())
                {
                    if(count!=gc.getCitiesCount())
                    {// not the first time
                        for (int i = 0; i < Prohibited_City_Names.size(); ++i)
                        {
                            if (Prohibited_City_Names.at(i) == query.value(0).toString())
                            {
                                flag = false;
                                break;
                            }

                        }
                    }
                    if(flag)
                    {
                        Ending_City_Names[index] = query.value(0).toString();
                        Kilometers[index++] = query.value(1).toDouble();
                        //flag = true;
                        size++;
                    }
                    flag = true;

                }

                int city_index=0; // respective city name index will be returned from function into the pointer
                min_kilometer = minFunction(Kilometers,size,&city_index);
                min_city = Ending_City_Names[city_index];

                Prohibited_City_Names.push_back(city);


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


               if(count > 1)
                    travelEfficiently(ui, model, min_city, --count, Prohibited_City_Names, row, column,total_kilometers);
               else
               {
                   QStandardItem *item2 = new QStandardItem(QString(QString::number(total_kilometers)+" Kilometers"));
                   model->setItem(--row,3,item2);
                   ui->tableView->update();
               }


}



int minFunction(double arr[], int size, int *index)
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



void EuropeanCities::on_tableView_doubleClicked(const QModelIndex &index)
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


