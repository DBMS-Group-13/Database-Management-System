#ifndef CREATETABLE_H
#define CREATETABLE_H

#include <QWidget>
#include "ui_createdb.h"
#include "qmath.h"
#include "qpainter.h"
#include "QMouseEvent"

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

private slots:
    void on_closeBut_clicked();
    void on_pushButton_clicked();

signals:
    textChange(QString, QString);
private:
    Ui::createTable *ui;
    QString DBname;
    QString tableName;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent * event);
    bool shouldMove = false;
    QPoint formerMainPos;
    QPoint formerMousePos;
};

#endif // CREATETABLE_H
