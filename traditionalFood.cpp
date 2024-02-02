#include "traditionalFood.h"
#include "ui_traditionalFood.h"
#include "dbhandler.h"

#include <QListView>
#include <QTableView>
#include <QTreeView>

void showReport(Ui::traditionalFood* ui);
void comboBoxLoad(Ui::traditionalFood* ui);
//================================================
traditionalFood::traditionalFood(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::traditionalFood)
{
    ui->setupUi(this);

    showReport(ui);
    comboBoxLoad(ui);
}
//================================================
traditionalFood::~traditionalFood()
{
    delete ui;
}
//================================================
void showReport(Ui::traditionalFood* ui)
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQueryModel* queryModel= new QSqlQueryModel;

        queryModel->setQuery("SELECT City, Food, Price FROM Foods WHERE IsActive=1 AND IsFoodActive=1");
        queryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("City"));
        queryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Traditional Food"));
        queryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
        ui->tableView->setModel(queryModel);
        ui->tableView->show();

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}
//================================================
void comboBoxLoad(Ui::traditionalFood* ui)
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
       // QString querystring = "SELECT City FROM Foods";
        QString querystring = "SELECT Name FROM Cities WHERE IsActive=1";

        QSqlQuery modelquery;

        modelquery.exec(querystring);
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(modelquery);
        model->setHeaderData(0, Qt::Horizontal, "City");

        ui->comboBox->setModel(model);

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}
//================================================
void traditionalFood::on_pushButton_selectCity_clicked()
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQueryModel* queryModel= new QSqlQueryModel;

        QString city = ui->comboBox->currentText();

        queryModel->setQuery("SELECT City, Food, Price FROM Foods WHERE City LIKE '%"+city+"%' AND IsActive=1 AND IsFoodActive=1");
        queryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("City"));
        queryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Traditional Food"));
        queryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
        ui->tableView->setModel(queryModel);
        ui->tableView->show();

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }
}
