QT       += core gui
QT       += core gui sql
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./main.cpp \
    ./mainwindow.cpp \
    database.cpp \
    login.cpp \
    newcolumn.cpp \
    newtable.cpp

HEADERS += \
    database.h \
    login.h \
    mainwindow.h \
    newcolumn.h \
    newtable.h

FORMS += \
    login.ui \
    mainwindow.ui \
    newcolumn.ui \
    newtable.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
