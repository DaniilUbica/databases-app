#include "mainwindow.h"
#include "qheaderview.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new Database;
    newColumn = new NewColumn;
    newTable = new NewTable;

    query = db->getQuery();
    model = db->getModel();

    db->createTable();
    db->setDatabase();

    ui->tableView->setModel(model);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setCombobox();
    setAllTables();
    setAllColumns();

    connect(newColumn, &NewColumn::confirmed, this, &MainWindow::addColumn);
    connect(newTable, &NewTable::confirmed, this, &MainWindow::addTable);
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

    ui->comboBox->clear();
    setCombobox();
}

void MainWindow::setCombobox()
{
    ui->comboBox->addItem("All");

    query->exec(QString("SELECT COUNT(*) FROM %1;").arg(ui->allTables->itemText(selectedTable)));

    query->first();

    int numberOfRows = query->value(0).toInt();

    query->prepare(QString("SELECT DISTINCT %1 FROM %2;").arg(ui->allColumns->itemText(selectedColumn), ui->allTables->itemText(selectedTable)));
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

void MainWindow::setAllTables()
{
    query->exec("SELECT COUNT(*) FROM sqlite_master;");

    query->first();

    int numberOfTables = query->value(0).toInt();

    query->prepare("SELECT name FROM sqlite_master WHERE type='table';");
    query->exec();

    for (int i = 0; i < numberOfTables; i++) {
        query->next();
        QString table = query->value(0).toString();
        ui->allTables->addItem(table);
    }
}

void MainWindow::setAllColumns()
{
    int numberOfColumns = model->columnCount();
    for (int i = 0; i < numberOfColumns; i++) {
        QVariant v = model->headerData(i, Qt::Horizontal, Qt::DisplayRole);
        QString name = v.toString();

        ui->allColumns->addItem(name);
    }
}

void MainWindow::onEnterPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Enter) {
        ui->comboBox->clear();
        setCombobox();
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    selectedItem = index;

    QString profession = ui->comboBox->itemText(selectedItem);
    QString filter;

    if (profession == "All") {
        filter = "";
    }
    else {
        filter = QString("%2 = '%1'").arg(profession, ui->allColumns->itemText(selectedColumn));
    }

    model->setFilter(filter);
}

void MainWindow::on_addColumn_clicked()
{
    newColumn->show();
}

void MainWindow::addColumn()
{
    newColumnName = newColumn->getColumnName();

    query->prepare(QString("ALTER TABLE %2 ADD COLUMN %1 TEXT;").arg(newColumnName, ui->allTables->itemText(selectedTable)));
    query->exec();

    QApplication::quit();
    QProcess::startDetached(QApplication::applicationFilePath());
}

void MainWindow::addTable()
{
    newTableName = newTable->getTableName();

    query->prepare(QString("CREATE TABLE %1(Field TEXT);").arg(newTableName));
    query->exec();

    ui->allTables->clear();
    setAllTables();

    QApplication::quit();
    QProcess::startDetached(QApplication::applicationFilePath());
}

void MainWindow::on_deleteColumn_clicked()
{
    QVariant v = model->headerData(db->selectedColumn, Qt::Horizontal, Qt::DisplayRole);
    QString name = v.toString();

    query->prepare(QString("ALTER TABLE %2 DROP COLUMN %1;").arg(name, ui->allTables->itemText(selectedTable)));
    query->exec();

    QApplication::quit();
    QProcess::startDetached(QApplication::applicationFilePath());
}

void MainWindow::on_addTable_clicked()
{
    newTable->show();
}

void MainWindow::on_allTables_activated(int index)
{
    selectedTable = index;

    QString table = ui->allTables->itemText(selectedTable);

    model->setTable(QString("%1").arg(table));
    model->select();

    ui->comboBox->clear();
    setCombobox();
    ui->allColumns->clear();
    setAllColumns();
}

void MainWindow::on_deleteTable_clicked()
{
    query->prepare(QString("DROP TABLE %1").arg(ui->allTables->itemText(selectedTable)));
    query->exec();

    ui->allTables->clear();
    setAllTables();
}

void MainWindow::on_allColumns_activated(int index)
{
    selectedColumn = index;

    ui->comboBox->clear();
    setCombobox();
}

