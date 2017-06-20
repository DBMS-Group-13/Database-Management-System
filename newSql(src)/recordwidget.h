#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>
#include "QPainter"
#include "QStandardItemModel"
#include "Entity/fieldentity.h"
#include "Entity/recordentity.h"
#include "qdebug.h"
#include "QMouseEvent"

namespace Ui {
class RecordWidget;
}

class RecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecordWidget(QWidget *parent = 0,QString DBName = "NULL",QString TabName = "NULL",
                          QString PRK = "NULL",QList<QString> UNList = QList<QString>()<<"NULL",QList<QString> NNList = QList<QString>()<<"NULL");
    void reflash();
    QStandardItemModel *tabModel;
    void exec();
    QHash<int,FieldEntity*> FNHash;
    QHash<int,RecordEntity*> QR;
    ~RecordWidget();

private slots:
    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_applyButton_clicked();

private:
    Ui::RecordWidget *ui;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent * event);
    bool shouldMove = false;
    QPoint formerMainPos;
    QPoint formerMousePos;

    QString PriKey;
    QList<QString> UN;
    QList<QString> NN;
    QString DBName;
    QString TabName;
    int isValid = 0;
signals:
    void hahaha(QHash<int,RecordEntity*>);
};

#endif // RECORDWIDGET_H
