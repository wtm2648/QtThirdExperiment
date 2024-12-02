#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    goLoginView();
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

void MasterView::goPatientEditView()
{
    qDebug() << "goPatientEditView";
    patienteditview = new PatientEditView(this);

    pushWidgetToStackView(patienteditview);
}

void MasterView::goPatientView()
{
    qDebug() << "goPatientView";
    patientview = new PatientView(this);

    pushWidgetToStackView(patientview);
}

void MasterView::goPreviousView()
{
    int cnt = ui->stackedWidget->count();

    if(cnt > 1){
        ui->stackedWidget->setCurrentIndex(cnt - 2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget = ui->stackedWidget->widget(cnt - 1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }

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

