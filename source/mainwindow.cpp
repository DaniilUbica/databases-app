#include "mainwindow.h"
#include "qheaderview.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new Database;
    newColumn = new NewColumn;

    query = db->getQuery();
    model = db->getModel();

    db->createTable();
    db->setDatabase();

    ui->tableView->setModel(model);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setCombobox();

    connect(newColumn, &NewColumn::confirmed, this, &MainWindow::addColumn);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete query;
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
    model->removeRow(db->selectedRow);
    setCombobox();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    db->selectedRow = index.row();
    db->selectedColumn = index.column();
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

void MainWindow::on_addColumn_clicked()
{
    newColumn->show();
}

void MainWindow::addColumn()
{
    newColumnName = newColumn->getColumnName();

    query->prepare(QString("ALTER TABLE Employees ADD COLUMN %1 TEXT;").arg(newColumnName));
    query->exec();
}


void MainWindow::on_deleteColumn_clicked()
{
    QVariant v = model->headerData(db->selectedColumn, Qt::Horizontal, Qt::DisplayRole);
    QString name = v.toString();

    query->prepare(QString("ALTER TABLE Employees DROP COLUMN %1;").arg(name));
    query->exec();
}

