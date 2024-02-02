#ifndef GLOBALVECTOR_H
#define GLOBALVECTOR_H

#include <QVector>



struct items
{
       int id;
       QString city;
       QString food;
       double price;
       int quantity;
};


 static QVector<items> _vector;


/*

 class GlobalData
 {
 public:
     struct items
     {
            int id;
            QString city;
            QString food;
            double price;
            int quantity;
     };


      static QVector<items> _vector;

 };*/

#endif // GLOBALVECTOR_H
