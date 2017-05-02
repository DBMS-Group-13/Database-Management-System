#include "loginWindow.h"
#include "centerwindow.h"
#include "ui_loginWindow.h"
#include<qpainter.h>
#include<qmath.h>
#include<qmovie.h>
#include<QPoint>
#include<QMouseEvent>
#include<QDebug>

loginWindow::loginWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    /*this->setWindowOpacity(0.0);*/
    this->setAttribute(Qt::WA_TranslucentBackground);
    QMovie *gif = new QMovie("LoginB.gif");
    ui->gifGround->setMovie(gif);
    gif->start();
    ui->passwordLine->setEchoMode(QLineEdit::Password);
    this->setMouseTracking(true);
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
    qDebug()<<ui->idLine->text()<<"\n"<<ui->passwordLine->text();
    centerwindow *p = new centerwindow(0,this->getUserid());
    p->show();
}
