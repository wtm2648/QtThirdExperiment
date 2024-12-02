#include "wellcomeview.h"
#include "ui_wellcomeview.h"
#include <QDebug>

WellcomeView::WellcomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WellcomeView)
{
    qDebug() << "Create WelcomeView";
    ui->setupUi(this);
}

WellcomeView::~WellcomeView()
{
    qDebug() << "Destroy WelcomeView";
    delete ui;
}
