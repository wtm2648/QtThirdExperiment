#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>
#include "idatabase.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);

    goLoginView();

    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    qDebug() << "goLoginView";
    loginview = new LoginView(this);

    pushWidgetToStackView(loginview);

    connect(loginview, SIGNAL(loginSuccess()),this,SLOT(goWelcomeView()));
}

void MasterView::goWelcomeView()
{
    qDebug() << "goWellcomeView";
    wellcomeview = new WellcomeView(this);

    pushWidgetToStackView(wellcomeview);

    connect(wellcomeview,SIGNAL(goDepartmentView()),this,SLOT(goDepartmentView()));
    connect(wellcomeview,SIGNAL(goDoctorView()),this,SLOT(goDoctorView()));
    connect(wellcomeview,SIGNAL(goPatientView()),this,SLOT(goPatientView()));
}

void MasterView::goDoctorView()
{
    qDebug() << "goDoctorView";
    doctorview = new DoctorView(this);

    pushWidgetToStackView(doctorview);
}

void MasterView::goDepartmentView()
{
    qDebug() << "goDepartmentView";
    departmentview = new DepartmentView(this);

    pushWidgetToStackView(departmentview);
}

void MasterView::goPatientEditView(int rowNum)
{
    qDebug() << "goPatientEditView";
    patienteditview = new PatientEditView(this, rowNum);

    pushWidgetToStackView(patienteditview);

    connect(patienteditview,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));
}

void MasterView::goPatientView()
{
    qDebug() << "goPatientView";
    patientview = new PatientView(this);

    pushWidgetToStackView(patientview);

    connect(patientview,SIGNAL(goPatientEditView(int)),this,SLOT(goPatientEditView(int)));
}

void MasterView::goPreviousView()
{
    int cnt = ui->stackedWidget->count();
    qDebug() << cnt;
    if(cnt > 1){
        ui->stackedWidget->setCurrentIndex(cnt - 2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget = ui->stackedWidget->widget(cnt - 1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
    cnt = ui->stackedWidget->count();
    qDebug() << cnt;
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int cnt = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(cnt - 1);
    ui->labelTitle->setText(widget->windowTitle());
}


void MasterView::on_btBack_clicked()
{
    goPreviousView();
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int cnt = ui->stackedWidget->count();
    if(cnt > 1){
        ui->btBack->setEnabled(true);
    }
    else
        ui->btBack->setEnabled(false);

    QString title = ui->stackedWidget->currentWidget()->windowTitle();
    if(title == "登录"){
        ui->btBack->setEnabled(false);
        ui->btLogout->setEnabled(false);
    }
    if(title == "欢迎"){
        ui->btBack->setEnabled(false);
        ui->btLogout->setEnabled(true);
    }
    else{
        ui->btLogout->setEnabled(false);
    }
}


void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}

