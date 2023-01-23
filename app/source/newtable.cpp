#include "newtable.h"
#include "ui_newtable.h"

NewTable::NewTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTable)
{
    ui->setupUi(this);
    this->setWindowTitle("New table edit");
}

NewTable::~NewTable()
{
    delete ui;
}

QString NewTable::getTableName()
{
    return tableName;
}

void NewTable::on_tableName_textChanged(const QString &arg1)
{
    tableName = arg1;
}

void NewTable::on_confirmButton_clicked()
{
    emit confirmed();
    this->close();
}

