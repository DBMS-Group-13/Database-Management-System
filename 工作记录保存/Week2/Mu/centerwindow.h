#ifndef CENTERWINDOW_H
#define CENTERWINDOW_H

#include <QWidget>
#include "QStandardItem"
#include "QMouseEvent"
#include "qmath.h"
#include "QDebug"
#include "qpainter.h"
#include "ui_centerwindow.h"
#include "createdb.h"
#include "createtable.h"

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
    void on_creDBBut_clicked();
    void on_close_clicked();
    bool creDBTree(QString DBname);
    bool creDBChildTree(QString DBname,QString tableName);
    void on_addTableBut_clicked();
    void on_treeview_clicked(const QModelIndex &index);

    void on_delTableBut_clicked();

private:
    Ui::centerwindow *ui;

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
};

#endif // CENTERWINDOW_H
