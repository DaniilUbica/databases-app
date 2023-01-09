#include "newcolumn.h"
#include "ui_newcolumn.h"

NewColumn::NewColumn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewColumn)
{
    ui->setupUi(this);
    this->setWindowTitle("New column edit");
}

NewColumn::~NewColumn()
{
    delete ui;
}

QString NewColumn::getColumnName()
{
    return columnName;
}

void NewColumn::on_columnName_textChanged(const QString &arg1)
{
    columnName = arg1;
}

void NewColumn::on_confirmButton_clicked()
{
    emit confirmed();
    this->close();
}

