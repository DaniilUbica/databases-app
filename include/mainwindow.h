#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <string>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createTable();

    void setDatabase();

private slots:

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_updateCombobox_clicked();

    void on_showProf_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    QSqlDatabase dataBase;
    QSqlQuery* query;
    QSqlTableModel* model;

    int selectedRow;
    int selectedItem;

    int generateID(int length);

    void setCombobox();
};
#endif // MAINWINDOW_H
