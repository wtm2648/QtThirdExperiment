#include "loginview.h"
#include "ui_loginview.h"
#include "idatabase.h"

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btLogIn_clicked()
{
    QString status=IDatabase::getInstance().userLogin(ui->inputUserName->text(),ui->inputUserPassword->text());
    if(status=="loginOK"){
        qDebug() << status;
        emit loginSuccess();
    }
    else{
        qDebug() << status;
    }
}

