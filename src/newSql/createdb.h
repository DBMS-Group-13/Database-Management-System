#ifndef CREATEDB_H
#define CREATEDB_H

#include <QWidget>
#include "ui_createdb.h"
#include "qmath.h"
#include "qpainter.h"
#include "QMouseEvent"

namespace Ui {
class createDB;
}

class createDB : public QWidget
{
    Q_OBJECT

public:
    explicit createDB(QWidget *parent = 0);
    QString dbName();
    void shakeWindow();
    ~createDB();

private slots:
    void on_closeBut_clicked();
    void on_pushButton_clicked();

private:
    Ui::createDB *ui;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent * event);
    bool shouldMove = false;
    QPoint formerMainPos;
    QPoint formerMousePos;
signals:
    void textChange(QString);
    void textChange2(QString,QString);
};

#endif // CREATEDB_H
