#ifndef NEWCOLUMN_H
#define NEWCOLUMN_H

#include <QDialog>

namespace Ui {
class NewColumn;
}

class NewColumn : public QDialog
{
    Q_OBJECT

public:
    explicit NewColumn(QWidget *parent = nullptr);
    ~NewColumn();

    QString getColumnName();

private slots:
    void on_columnName_textChanged(const QString &arg1);

    void on_confirmButton_clicked();

signals:
    void confirmed();

private:
    Ui::NewColumn *ui;
    QString columnName;
};

#endif // NEWCOLUMN_H
