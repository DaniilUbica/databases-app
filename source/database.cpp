#include "database.h"
#include "qsqlquery.h"

Database::Database()
{
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("./EmployeesDatabase.db");

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
    query->prepare("CREATE TABLE Employees(Firstname TEXT, Lastname TEXT, ID INT, Profession TEXT);");
    query->exec();
}

void Database::setDatabase()
{
    model->setTable("Employees");
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

