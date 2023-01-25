#include "login.h"
#include "ui_login.h"

#include <QDebug>

LogIn::LogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);

    socket->connectToHost("127.0.0.1", 7878);

    connect(socket, &QTcpSocket::readyRead, this, &LogIn::readyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

LogIn::~LogIn()
{
    delete ui;
    delete socket;
    delete mainWindow;
}

void LogIn::readyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok) {
        QString str;
        in >> str;
        if (str.size() > 0) {
            mainWindow = new MainWindow(databaseName);
            ui->infoLabel->setText("Access granted");
            this->close();
            mainWindow->show();
        }
        else {
            ui->infoLabel->setText("Can't log in (You can try to check in)");
        }
    }
    else {
        ui->infoLabel->setText("Error, please, try to restart app");
    }
}

void LogIn::on_logIn_clicked()
{
    QString nick, password;

    nick = ui->nickEdit->text();
    password = ui->passwordEdit->text();
    databaseName = ui->databaseEdit->text();

    std::vector<QString> vec = {nick, password};
    this->send(vec);
}


void LogIn::on_checkIn_clicked()
{
    QString nick, password;

    nick = ui->nickEdit->text();
    password = ui->passwordEdit->text();
    databaseName = ui->databaseEdit->text();

    std::vector<QString> vec = {nick, password, databaseName};
    this->send(vec);
}

void LogIn::send(std::vector<QString>& data)
{
    Data.clear();
    QString str;
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);

    if (data.size() == 3) {
        str = "R " + data[0] + " " + data[1] + " " + data[2];
    }
    if (data.size() == 2) {
        str = "L " + data[0] + " " + data[1];
    }

    out << str;
    socket->write(Data);
}

