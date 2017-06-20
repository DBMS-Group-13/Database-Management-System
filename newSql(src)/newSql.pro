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
    createtable.cpp \
    DataOps/dbdataops.cpp \
    DataOps/recorddataops.cpp \
    DataOps/tabledataops.cpp \
    Entity/dbentity.cpp \
    Entity/fieldentity.cpp \
    Entity/recordentity.cpp \
    Entity/tableentity.cpp \
    Logic/dblogic.cpp \
    Logic/filelogic.cpp \
    Logic/recordlogic.cpp \
    Logic/service.cpp \
    Logic/tablelogic.cpp \
    Util/appexception.cpp \
    Util/filehelper.cpp \
    Util/typehelper.cpp \
    recordwidget.cpp \
    rnwindow.cpp

HEADERS  += loginWindow.h \
    centerwindow.h \
    createdb.h \
    createtable.h \
    DataOps/dbdataops.h \
    DataOps/recorddataops.h \
    DataOps/tabledataops.h \
    Entity/dbentity.h \
    Entity/fieldentity.h \
    Entity/recordentity.h \
    Entity/tableentity.h \
    Global/datastructure.h \
    Global/ref.h \
    Logic/dblogic.h \
    Logic/filelogic.h \
    Logic/recordlogic.h \
    Logic/service.h \
    Logic/tablelogic.h \
    Util/appexception.h \
    Util/filehelper.h \
    Util/typehelper.h \
    recordwidget.h \
    rnwindow.h

FORMS    += loginWindow.ui \
    centerwindow.ui \
    createdb.ui \
    createtable.ui \
    recordwidget.ui \
    rnwindow.ui

RESOURCES += \
    resource.qrc
