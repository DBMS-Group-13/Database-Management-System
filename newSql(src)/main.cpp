#include "loginWindow.h"
#include"centerwindow.h"
#include"createdb.h"
#include"createtable.h"
#include "qtextcodec.h"
#include "Entity/recordentity.h"
#include "Entity/fieldentity.h"
#include "Logic/service.h"
#include "rnwindow.h"
#include "Logic/filelogic.h"
#include "recordwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //FileLogic::setUser("root");
    loginWindow w;
    //centerwindow *w = new centerwindow(0,"root");
//    rnWindow w;
    w.show();

    return a.exec();
}
