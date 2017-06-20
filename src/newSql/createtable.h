#ifndef CREATETABLE_H
#define CREATETABLE_H

#include <QWidget>
#include "ui_createdb.h"
#include "qmath.h"
#include "qpainter.h"
#include "QStandardItem"
#include "qtablewidget.h"
#include "qdebug.h"
#include "QMouseEvent"
#include "QItemDelegate"

namespace Ui {
class createTable;
}

class createTable : public QWidget
{
    Q_OBJECT

public:
    explicit createTable(QWidget *parent = 0, QString _DBname = "DBname_default");
    ~createTable();

    void setDBName(QString name);
    void shakeWindow();
    void setTabName(QString name);

    int isVaild = 0;
    void reflashTable();
    void setBeginPos(int size);
    QStandardItemModel *tabModel;

private slots:
    void on_closeBut_clicked();
    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_flashButton_clicked();

signals:
    void textChange(QString, QString);
    void fieldChange(QString, QString,QString,QString,QString,QString,QString,QString);
private:
    int shouldChange = 0;
    Ui::createTable *ui;
    QString DBname;
    QString tableName;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent * event);
    void iniTab();
    bool shouldMove = false;
    QPoint formerMainPos;
    QPoint formerMousePos;
    int beginPos = 0;
};

#endif // CREATETABLE_H
