#ifndef DATABASE_H
#define DATABASE_H

#include <QDate>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#define DATABASE_HOSTNAME "ExampleDataBase"
#define DATABASE_NAME "lab4.db"

#define TABLE_TEACH "teacher"
#define TEACH_ID "teacher_id"
#define TEACH_FIO "fio"
#define TEACH_DATE "date_of_birth"
#define TEACH_POS "position_id"
#define TEACH_DEP "department_id"

#define TABLE_POSITION "position"
#define POS_ID "position_id"
#define POS_NAME "name"

#define TABLE_DEPARTMENT "department"
#define DEP_ID "department_id"
#define DEP_NAME "name"


class DataBase : public QObject
{
    Q_OBJECT
  public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    void connectToDataBase();
    bool inserIntoMainTable(const QVariantList &data);
    bool inserIntoDeviceTable(const QVariantList &data);

  private:
    QSqlDatabase db;

  private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createMainTable();
    bool createDeviceTable();
};

#endif   // DATABASE_H
