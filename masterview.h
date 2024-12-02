#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "wellcomeview.h"
#include "doctorview.h"
#include "departmentview.h"
#include "patienteditview.h"
#include "patientview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MasterView; }
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void goLoginView();
    void goWelcomeView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientEditView();
    void goPatientView();
    void goPreviousView();

private slots:
    void on_btBack_clicked();

private:
    void pushWidgetToStackView(QWidget *widget);

    Ui::MasterView *ui;

    WellcomeView *wellcomeview;
    DoctorView *doctorview;
    PatientEditView *patienteditview;
    DepartmentView *departmentview;
    LoginView *loginview;
    PatientView *patientview;
};
#endif // MASTERVIEW_H
