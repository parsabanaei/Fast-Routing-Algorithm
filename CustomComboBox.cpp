#include "CustomComboBox.h"
#include <foodpurchase.cpp>
//#include <purchaseform.cpp>


 //====================================== Cunstructor ========================================
CustomComboBox::CustomComboBox(int _id, QString _city, QString _food, double _price)
{
    city= _city;
    food= _food;
    price= _price;
    id = _id;

    QObject::connect(this,&QComboBox::currentIndexChanged, this, &CustomComboBox::onCurrentIndexChanged);
 }



CustomComboBox::CustomComboBox()
{

}


//====================================== Slot ========================================
void CustomComboBox::onCurrentIndexChanged(int value)
{
    if (value != 0) {

        for(int i = 0 ; i < _vector.size() ; i++)
        {
            if(_vector[i].id == id)
            {
                _vector.remove(i);
            }
        }


        items structItems;
        structItems.id = id;
        structItems.city = city;
        structItems.food = food;
        structItems.price = price;
        structItems.quantity = value;
        _vector.push_back(structItems);

        //msgBox.setText("City: "+city +"\n food: "+food+ "\n price:"+QString::number(price)+"\n index: "+QString::number(value));
        //msgBox.exec();

        //msgBox.setText(QString::number(_vector.size()));
        //msgBox.exec();

    }
    else if(value==0)
    {
        for(int i = 0 ; i < _vector.size() ; i++)
        {
            if(_vector[i].id == id)
            {
               _vector.remove(i);
            }
        }

    }
}





void CustomComboBox::purchaseItems()
{
        QMessageBox msgBox;
       // QSqlQuery qry;
       //QSqlQuery query;
        QString city;
        QString food;
        QString price;
        QString quantity;
        QString totalPriceStr;


        //msgBox.setText(QString::number(_vector.size()));
        //msgBox.exec();


        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {

            QString str="";
            double totalPrice;
            str += "Purchased Items:\n\n";
            for(int i = 0 ; i < _vector.size() ; i++)
            {
                 city = _vector[i].city;
                 food = _vector[i].food;
                 price = QString::number(_vector[i].price);
                 quantity = QString::number(_vector[i].quantity);


                str +="ID:  " + QString::number(_vector[i].id)+" \n";
                str +="City:  " + city+" \n";
                str +="Food:  " + food+" \n";
                str +="Price:  " + price+"$ US \n";
                str +="Quntity:  " + quantity+" \n";
                totalPrice = _vector[i].price*_vector[i].quantity;
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
            _vector.clear();
        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
        }
}
