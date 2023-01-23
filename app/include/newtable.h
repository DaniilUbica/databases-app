#ifndef NEWTABLE_H
#define NEWTABLE_H

#include <QDialog>

namespace Ui {
class NewTable;
}

class NewTable : public QDialog
{
    Q_OBJECT

public:
    explicit NewTable(QWidget *parent = nullptr);
    ~NewTable();

    QString getTableName();

private slots:
    void on_tableName_textChanged(const QString &arg1);

    void on_confirmButton_clicked();

signals:
    void confirmed();

private:
    Ui::NewTable *ui;
    QString tableName;
};

#endif // NEWTABLE_H
