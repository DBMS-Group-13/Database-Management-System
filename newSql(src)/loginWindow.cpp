#include "loginWindow.h"
#include "centerwindow.h"
#include "ui_loginWindow.h"
#include<qpainter.h>
#include<qmath.h>
#include<qmovie.h>
#include<QPoint>
#include<QMouseEvent>
#include<QDebug>
#include"qpropertyanimation.h"

loginWindow::loginWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    //this->setStyleSheet("QWidget{border-radius:15px;border-top-right-radius:5px;}");
    this->setWindowFlags(Qt::FramelessWindowHint);
    /*this->setWindowOpacity(0.0);*/
    QRegExp regExp("[_a-zA-Z0-9]+$");
    ui->idLine->setValidator(new QRegExpValidator(regExp, ui->idLine));
    this->setAttribute(Qt::WA_TranslucentBackground);
    QMovie *gif = new QMovie(":/Login/gif/resources/LoginB.gif");
    ui->passwordLine->setEchoMode(QLineEdit::Password);
    this->setMouseTracking(true);
    ui->gifGround->setMovie(gif);
    gif->start();
}

loginWindow::~loginWindow()
{
    delete ui;
}

QString loginWindow::getUserid(){
    return ui->idLine->text();
}

void loginWindow::mousePressEvent (QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = true;
        formerMainPos = this->pos();
        formerMousePos = event->globalPos();
    }

void loginWindow::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = false;
    }

void loginWindow::mouseMoveEvent ( QMouseEvent * event )
    {
        QPoint pos = event->globalPos();

        if (shouldMove)
        {
            int x = pos.x()-formerMousePos.x();
            int y = pos.y()-formerMousePos.y();
            move(formerMainPos.x()+x,formerMainPos.y()+y);
        }
    }

void loginWindow::paintEvent(QPaintEvent *event)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

void loginWindow::shakeWindow(){
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");
    pAnimation->setDuration(500);
    pAnimation->setLoopCount(2);
    pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(1, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}


/*
 * 给你们看的内容
*/

//登录界面退出按钮
void loginWindow::on_closeBut_clicked()
{
    exit(0);
}
//登陆按钮单击事件
void loginWindow::on_signBut_clicked()
{
    int isValid = -1;
    qDebug()<<ui->idLine->text()<<"\n"<<ui->passwordLine->text();
    FileLogic::setUser("root");
    service sv;
    sv.LoadRecord("newSql","user");
    QHash<int,RecordEntity*> QR = sv.getRecordArr();
    for(int i = 0;i < QR.size();i++){
        QHash<QString,QString> QQ;
        QQ = QR.value(i)->getReArr();
        qDebug()<<QQ;
        if(QQ.value("name") == ui->idLine->text() && QQ.value("password") == ui->passwordLine->text()){
            isValid = 0;
        }
    }
        if(isValid == -1){
            this->shakeWindow();
            return;
        }
    FileLogic::setUser(this->getUserid());
    centerwindow *p = new centerwindow(0,this->getUserid());
    p->show();
    this->close();
}
