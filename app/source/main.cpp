#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogIn l;
    l.setWindowTitle("Log in");
    l.show();
    return a.exec();
}
