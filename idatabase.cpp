#include "idatabase.h"
#include <QUuid>

void IDatabase::initDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = "../../lb4d.db";
    database.setDatabaseName(aFile);
    database.setPassword("wufulin951753.");

    if(!database.open()){
        qDebug() << "Fail to open the database." << database.lastError().text();
    }
    else{
        qDebug() << "Open database succeed";
    }
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this, database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);  //数据保存方式，还有一种是OnRowChange
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);  //排序
    if(!patientTabModel->select()){
        return false;
    }
    thePatientSelection = new QItemSelectionModel(patientTabModel);
    return true;
}

int IDatabase::addNewPatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(), QModelIndex());  //在末行添加一个记录
    QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount() - 1, 1);  //创建最后一行的ModelIndex
    int curRecNo = curIndex.row();
    QSqlRecord curRec = patientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));
    patientTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    return patientTabModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    patientTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString userPassword)
{
    QSqlQuery query;
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER",userName);
    query.exec();
    if(query.first() && query.value("username").isValid()){
        QString password = query.value("password").toString();
        if(password==userPassword){
            return "loginOK";
        }
        else{
            return "wrongPassword";
        }
    }
    else{
        return "wrongUsername";
    }
}

IDatabase::IDatabase(QObject *parent) : QObject(parent)
{
    initDatabase();
}
