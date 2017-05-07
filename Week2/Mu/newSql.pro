#-------------------------------------------------
#
# Project created by QtCreator 2017-04-28T15:19:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newSql
TEMPLATE = app


SOURCES += main.cpp\
        loginWindow.cpp \
    centerwindow.cpp \
    createdb.cpp \
    createtable.cpp

HEADERS  += loginWindow.h \
    centerwindow.h \
    createdb.h \
    createtable.h

FORMS    += loginWindow.ui \
    centerwindow.ui \
    createdb.ui \
    createtable.ui

RESOURCES += \
    resource.qrc
