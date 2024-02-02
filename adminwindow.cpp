#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "dbhandler.h"
#include "adminpanel.h"


AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_checkBox_stateChanged(int arg1)
{
    //ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    ui->checkBox->checkState() ? ui->passwordLineEdit->setEchoMode(QLineEdit::Normal) :ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}


void AdminWindow::on_pushButton_clicked()
{


    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);

    if(dbHandler.open())
    {
        QSqlQuery query;

        QString username = ui->usernameLineEdit->text();
        QString password = ui->passwordLineEdit->text();
        QString result;

        if(query.exec("SELECT ID FROM Account WHERE Username='"+username+"' AND Password='"+password+"'"))
        {
            query.next();
            result = query.value(0).toString();
            if(result=="")
            {
                msgBox.setText("incorrect!");
                msgBox.exec();
            }
            else
            {
                //msgBox.setText("Successful!");
                //msgBox.exec();

               AdminPanel *form;
               form=new AdminPanel(this);
               form->show();
               close();


                    //ManagerWindow *managerForm;
                    //hide();
                   // managerForm = new ManagerWindow(this);
                    //managerForm->show();
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

