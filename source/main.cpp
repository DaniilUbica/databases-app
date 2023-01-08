#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Employees database");
    w.createTable();
    w.setDatabase();
    w.show();
    return a.exec();
}
