#include "database.h"
#include "qsqlquery.h"

Database::Database(QString name)
{
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("./Databases/" + name + ".db");

    if (!dataBase.open()){
        throw "Can`t open database!";
    }

    query = new QSqlQuery(dataBase);
    model = new QSqlTableModel();
}

Database::~Database()
{
    delete query;
    delete model;
}

void Database::createTable()
{
    query->prepare("CREATE TABLE Start(First TEXT);");
    query->exec();
}

void Database::setDatabase()
{
    model->setTable("Start");
    model->select();
}

QSqlTableModel* Database::getModel()
{
    return model;
}

QSqlQuery* Database::getQuery()
{
    return query;
}

