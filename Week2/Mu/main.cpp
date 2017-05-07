#include "loginWindow.h"
#include"centerwindow.h"
#include"createdb.h"
#include"createtable.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //loginWindow w;
    centerwindow w;
    //createDB w;
    //createTable *w = new createTable(0,"DB15301148");
    w.show();

    return a.exec();
}
