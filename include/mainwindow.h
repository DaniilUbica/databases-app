#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableWidgetItem>

#include "database.h"
#include "newcolumn.h"

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

    void on_updateCombobox_clicked();

    void on_showProf_clicked();

    void on_comboBox_activated(int index);

    void on_addColumn_clicked();

    void on_deleteColumn_clicked();

public slots:
    void addColumn();

private:
    Ui::MainWindow *ui;
    Database* db;
    QSqlTableModel* model;
    QSqlQuery* query;
    NewColumn* newColumn;

    int selectedItem;

    QString newColumnName;

    void setCombobox();
};
#endif // MAINWINDOW_H
