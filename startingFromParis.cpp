#include "startingFromParis.h"
#include "ui_startingFromParis.h"
#include "dbhandler.h"
//#include"europeancities.cpp"
#include "foodpurchase.h"
#include "purchaseform.h"

#include<QTextEdit>
#include<QLineEdit>
#include <QStandardItemModel>
#include <QDebug>


//prototype
int minFunction2(double arr[], int size, int *index);

//prototype
void travelEfficiently(Ui::startingFromParis* ui,QStandardItemModel *model, QString city,
                      int count,QVector<QString> Prohibited_City_Names,
                      int row, int column,double total_kilometers);


void _initial();
int count_of_cities;

startingFromParis::startingFromParis(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::startingFromParis)
{
    ui->setupUi(this);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    count_of_cities=0;
    _initial();


}
//===================================================================================
startingFromParis::~startingFromParis()
{
    delete ui;
}
//===================================================================================

void startingFromParis:: on_pushButton_enterNumOfCities_clicked()
{
    QMessageBox msgBox;

    // number entered by traveler is stored in variable "num"
    int num = ui->lineEdit->text().toInt();

    if(num>=1 && num<count_of_cities)
    {
        //qDebug() << ui->lineEdit->text().toInt();
        //qDebug() << num;

        // clears the number entered by taveler
        ui -> lineEdit -> clear();



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


            QString city = "paris";

            QVector<QString> Prohibited_City_Names;
            double total_kilometers = 0;

            // call to the recursive function
            travelEfficiently(ui,model,city,num,Prohibited_City_Names,0,0,total_kilometers);

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
        QMessageBox msgBox;
        msgBox.setText("invalid entry! try again");
        msgBox.exec();
    }

}
//===================================================================================
void startingFromParis ::on_tableView_doubleClicked(const QModelIndex &index)
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
//===================================================================================
int minFunction2(double arr[], int size, int *index)
{
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

//===================================================================================
void travelEfficiently(Ui::startingFromParis* ui,QStandardItemModel *model, QString city,
                      int count,QVector<QString> Prohibited_City_Names,
                      int row, int column,double total_kilometers)
{
    QSqlQuery query;
    QString Ending_City_Names[count_of_cities];
    double Kilometers[count_of_cities];
    int index = 0;
    QString min_city;
    double min_kilometer;

    bool flag = true;
    int size = 0;

    query.exec("SELECT Ending_City_Name, Kilometers FROM Distances WHERE Starting_City_Name LIKE '%"+city+"%' AND IsActive=1");
                while(query.next())
                {
                    if(count!=count_of_cities)
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
                min_kilometer = minFunction2(Kilometers,size,&city_index);
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





void _initial()
{
    QMessageBox msgBox;


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQuery query;
        query.exec("SELECT Name FROM Cities WHERE IsActive=1");
        while(query.next())
        {
            count_of_cities+=1;
            //cities_Queue.enqueue(query.value(0).toString());

        }

            //query.prepare("SELECT COUNT(*) FROM Cities WHERE IsActive=1");
            //query.exec();
            //query.first();

        //count_of_cities = query.value(0).toInt();;

        //msgBox.setText(QString::number(count_of_cities));
        //msgBox.exec();

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}
