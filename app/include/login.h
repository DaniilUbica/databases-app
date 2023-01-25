#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QTcpSocket>

#include "mainwindow.h"
#include "database.h"

namespace Ui {
class LogIn;
}

class LogIn : public QDialog
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

public slots:
    void readyRead();

private slots:
    void on_logIn_clicked();

    void on_checkIn_clicked();

private:
    Ui::LogIn *ui;
    MainWindow* mainWindow;
    QTcpSocket* socket;
    QByteArray Data;
    QString databaseName;

    void send(std::vector<QString>& data);
};

#endif // LOGIN_H
