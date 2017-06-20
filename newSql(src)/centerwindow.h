#ifndef CENTERWINDOW_H
#define CENTERWINDOW_H

#include <QWidget>
#include "QStandardItem"
#include "QMouseEvent"
#include "qmath.h"
#include "QDebug"
#include "qpainter.h"
#include "qpoint.h"
#include "ui_centerwindow.h"
#include "createdb.h"
#include "createtable.h"
#include "qmenu.h"
#include "Logic/service.h"
#include "Entity/dbentity.h"
#include "Entity/fieldentity.h"
#include "Entity/recordentity.h"
#include "Entity/tableentity.h"
#include "rnwindow.h"
#include "recordwidget.h"

namespace Ui {
class centerwindow;
}

class centerwindow : public QWidget
{
    Q_OBJECT

public:
    explicit centerwindow(QWidget *parent = 0, QString userid = "default user");
    ~centerwindow();


private slots:
    bool creDBTree(QString DBname);
    bool creDBChildTree(QString DBname,QString tableName);
    void changeRecord(QHash<int,RecordEntity*> QR);
    void deleteField(QString name);
    void showRenameWid();
    void delField();
    void rename(QString name);

    void on_creDBBut_clicked();
    void on_close_clicked();
    void on_addTableBut_clicked();
    void on_treeview_clicked(const QModelIndex &index);
    void on_delTableBut_clicked();
    void on_dropDBBut_clicked();
    void on_treeview_doubleClicked();
    void on_tableView_customContextMenuRequested(const QPoint &pos);
    void on_treeview_customContextMenuRequested(const QPoint &pos);
    bool creFieldEntity(QString DB, QString TAB, QString FN, QString TP,
                        QString PR, QString NN, QString UN,QString def);


private:
    Ui::centerwindow *ui;

    service *mySer;
    QString tn = "null";
    //QString lalala = "null";
    bool addDBTree(QString DBname);
    bool addTabTree(QString DBName,QString tableName);
    void paintEvent(QPaintEvent *event);
    void initTree(QString userid);
    void initStatus(QString userid);
    void creTableWidget();
    void creTableWidgetDB();

    QStandardItemModel *treeModel;
    QStandardItemModel *tabModel;

    createDB *creDB;
    QString selectDBName;
    QString selectTableName;
    QString user;
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent * event);
    bool shouldMove = false;
    QPoint formerMainPos;
    QPoint formerMousePos;
    createTable *creTab;
    RecordWidget *rw;
};

#endif // CENTERWINDOW_H
