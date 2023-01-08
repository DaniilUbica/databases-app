#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("./EmployeesDB.db");

    if (!dataBase.open()){
        throw "Can`t open database!";
    }

    query = new QSqlQuery(dataBase);
    model = new QSqlTableModel(this, dataBase);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setCombobox();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete query;
    delete model;
}

void MainWindow::createTable()
{
    query->prepare("CREATE TABLE Employees(Firstname TEXT, Lastname TEXT, ID INT, Profession TEXT);");
    query->exec();
}

void MainWindow::setDatabase()
{
    model->setTable("Employees");
    model->select();

    ui->tableView->setModel(model);
}

void MainWindow::on_addButton_clicked()
{
    ui->comboBox->clear();
    model->insertRow(model->rowCount());
    setCombobox();
}


void MainWindow::on_deleteButton_clicked()
{
    ui->comboBox->clear();
    model->removeRow(selectedRow);
    setCombobox();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    selectedRow = index.row();
}

int MainWindow::generateID(int length)
{
    srand(time(NULL));

    std::string retStr = "";
    for(int i = 0; i < length; i++){
        retStr += std::to_string(rand() % 9 + 0);
    }

    return std::stoi(retStr);
}

void MainWindow::setCombobox()
{
    ui->comboBox->addItem("All professions");

    query->exec("SELECT COUNT(*) FROM Employees;");

    query->first();

    int numberOfRows = query->value(0).toInt();

    query->prepare("SELECT DISTINCT Profession FROM Employees;");
    query->exec();

    for (int i = 0; i < numberOfRows; i++) {
        query->next();
        QString prof = query->value(0).toString();
        ui->comboBox->addItem(prof);
    }

    int size = ui->comboBox->count();
    for (int i = 0; i < size; i++) {
        if (ui->comboBox->itemText(i) == "") {
            ui->comboBox->removeItem(i);
        }
    }

}

void MainWindow::on_updateCombobox_clicked()
{
    ui->comboBox->clear();
    setCombobox();
}

void MainWindow::on_showProf_clicked()
{
    QString profession = ui->comboBox->itemText(selectedItem);
    QString filter;

    if (profession == "All professions") {
        filter = "";
    }
    else {
        filter = QString("Profession = '%1'").arg(profession);
    }

    model->setFilter(filter);
}

void MainWindow::on_comboBox_activated(int index)
{
    selectedItem = index;
}

