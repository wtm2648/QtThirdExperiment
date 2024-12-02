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

}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int cnt = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(cnt - 1);
    ui->labelTitle->setText(widget->windowTitle());
}

