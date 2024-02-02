#ifndef GLOBALCITIESARRAY_H
#define GLOBALCITIESARRAY_H

#include "dbhandler.h"
#include <QQueue>
#include <QStack>



class GlobalCities
{
public:
    int count_of_cities;
    QQueue<QString> cities_Queue;
    QStack<QString> cities_Stack;

    void initial()
    {
        QMessageBox msgBox;

        count_of_cities=0;
        cities_Queue.clear();
        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query;
            query.exec("SELECT Name FROM Cities WHERE IsActive=1");
            while(query.next())
            {
                count_of_cities+=1;
                cities_Queue.enqueue(query.value(0).toString());

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

    int getCitiesCount()
    {
        return count_of_cities;
    }

    QQueue<QString> getCitiesQueue()
    {
        return cities_Queue;
    }

    QStack<QString> getCitiesStack()
    {
        return cities_Stack;
    }
};

//static QString cities_Array[count_of_cities];







#endif // GLOBALCITIESARRAY_H
