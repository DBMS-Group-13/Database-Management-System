#include "rnwindow.h"
#include "ui_rnwindow.h"
#include "qpropertyanimation.h"

rnWindow::rnWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rnWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QRegExp regExp("[_a-zA-Z0-9]+$");
    ui->lineEdit->setValidator(new QRegExpValidator(regExp, ui->lineEdit));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowModality(Qt::ApplicationModal);
}

rnWindow::~rnWindow()
{
    delete ui;
}

void rnWindow::paintEvent(QPaintEvent *event)
{
        QPainter painter2(this);
        painter2.setRenderHint(QPainter::Antialiasing);  // �����;
        painter2.setBrush(QBrush(QColor::fromRgb(45,64,79)));
        painter2.setPen(Qt::transparent);
        QRect rect = this->rect();
        rect.setWidth(rect.width() - 1);
        rect.setHeight(rect.height() - 1);
        painter2.drawRoundedRect(rect, 15, 15);
        //Ҳ����QPainterPath ���ƴ��� painter.drawRoundedRect(rect, 15, 15);
        {
            QPainterPath painterPath;
            painterPath.addRoundedRect(rect, 15, 15);
            painter2.drawPath(painterPath);
        }
        QWidget::paintEvent(event);
}

void rnWindow::mousePressEvent (QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = true;
        formerMainPos = this->pos();
        formerMousePos = event->globalPos();
    }

void rnWindow::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = false;
    }

void rnWindow::mouseMoveEvent ( QMouseEvent * event )
    {
        QPoint pos = event->globalPos();
        if (shouldMove)
        {
            int x = pos.x()-formerMousePos.x();
            int y = pos.y()-formerMousePos.y();
            move(formerMainPos.x()+x,formerMainPos.y()+y);
        }
    }

void rnWindow::shakeWindow(){
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");
    pAnimation->setDuration(500);
    pAnimation->setLoopCount(2);
    pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 3, geometry().y()));
    pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 6, geometry().y()));
    pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 6, geometry().y()));
    pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 6, geometry().y()));
    pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 6, geometry().y()));
    pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 6, geometry().y()));
    pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 6, geometry().y()));
    pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 6, geometry().y()));
    pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 6, geometry().y()));
    pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() + 6, geometry().y()));
    pAnimation->setKeyValueAt(1, QPoint(geometry().x() - 3, geometry().y()));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void rnWindow::on_cancelBut_clicked()
{
    this->close();
}

void rnWindow::on_appluBut_clicked()
{
    if(ui->lineEdit->text()!="")
    emit emlit(ui->lineEdit->text());
    this->close();
}
