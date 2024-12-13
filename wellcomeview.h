#ifndef WELLCOMEVIEW_H
#define WELLCOMEVIEW_H

#include <QWidget>

namespace Ui {
class WellcomeView;
}

class WellcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WellcomeView(QWidget *parent = nullptr);
    ~WellcomeView();

private slots:

    void on_Department_clicked();

    void on_Doctor_clicked();

    void on_Patient_clicked();

signals:
    void goDepartmentView();
    void goDoctorView();
    void goPatientView();

private:
    Ui::WellcomeView *ui;
};

#endif // WELLCOMEVIEW_H
