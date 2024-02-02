#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "europeancities.h"
#include "adminwindow.h"
#include "traditionalFood.h"
#include "foodpurchase.h"
#include "purchasehistory.h"
#include "startingFromParis.h"
#include "customtrip.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    EuropeanCities *form;
    //hide();
    form = new EuropeanCities(this);
    form->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    AdminWindow *form;
    //hide();
    form = new AdminWindow(this);
    form->show();
}

void MainWindow::on_pushButton_displayFood_clicked()
{
    traditionalFood *form;
    //hide();
    form = new traditionalFood(this);
    form->show();
}

void MainWindow::on_pushButton_displayFood_2_clicked()
{
    FoodPurchase *form;
    //hide();
    form = new FoodPurchase(this);
    form->show();
}


void MainWindow::on_pushButton_displayFood_3_clicked()
{
    PurchaseHistory *form;
    //hide();
    form = new PurchaseHistory(this);
    form->show();
}

void MainWindow::on_pushButton_startingFromParis_clicked()
{
    startingFromParis *form;
    //hide();
    form = new startingFromParis(this);
    form->show();
}

void MainWindow::on_pushButton_startingFromParis_2_clicked()
{
    CustomTrip *form;
    //hide();
    form = new CustomTrip(this);
    form->show();
}

