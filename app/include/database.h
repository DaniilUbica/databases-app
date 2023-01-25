#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <string>
#include <cmath>

class Database
{
public:
    int selectedRow;
    int selectedColumn;

    Database(QString name);
    ~Database();

    void createTable();

    void setDatabase();

    QSqlTableModel* getModel();

    QSqlQuery* getQuery();

private:
    QSqlDatabase dataBase;
    QSqlQuery* query;
    QSqlTableModel* model;
};

#endif // DATABASE_H
