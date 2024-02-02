#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "admineditwindow.h"
#include "adminmaintenance.h"

AdminPanel::AdminPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPanel)
{
    ui->setupUi(this);
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::on_add_distance_button_1_clicked()
{
    AdminEditWindow *form;
    //hide();
    form = new AdminEditWindow(this);
    form->show();
    //close();
}


void AdminPanel::on_add_distance_button__clicked()
{
    AdminMaintenance *form;
    //hide();
    form = new AdminMaintenance(this);
    form->show();
    //close();
}

