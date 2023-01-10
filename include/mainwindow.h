#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableWidgetItem>
#include <QKeyEvent>

#include "database.h"
#include "newcolumn.h"
#include "newtable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_activated(int index);

    void on_addColumn_clicked();

    void on_deleteColumn_clicked();

    void on_addTable_clicked();

    void on_allTables_activated(int index);

    void on_deleteTable_clicked();

    void on_allColumns_activated(int index);

public slots:
    void addColumn();

    void addTable();

private:
    Ui::MainWindow *ui;
    Database* db;
    QSqlTableModel* model;
    QSqlQuery* query;
    NewColumn* newColumn;
    NewTable* newTable;

    int selectedItem;
    int selectedTable;
    int selectedColumn;

    QString newColumnName;
    QString newTableName;

    void setCombobox();

    void setAllTables();

    void setAllColumns();

    void onEnterPressEvent(QKeyEvent* event);
};
#endif // MAINWINDOW_H
