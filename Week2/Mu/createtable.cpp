#include "createtable.h"
#include "ui_createtable.h"
#include "qpropertyanimation.h"

createTable::createTable(QWidget *parent, QString _DBname) :
    QWidget(parent),
    ui(new Ui::createTable)
{
    DBname = _DBname;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowModality(Qt::ApplicationModal);
    QRegExp regExp("[_a-zA-Z0-9]+$");
    ui->dbName->setValidator(new QRegExpValidator(regExp, ui->dbName));
    ui->tableName->setValidator(new QRegExpValidator(regExp, ui->tableName));
    ui->dbName->setText(DBname);
}

createTable::~createTable()
{
    delete ui;
}

void createTable::paintEvent(QPaintEvent *event)
{
        QPainter painter2(this);
        painter2.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
        painter2.setBrush(QBrush(QColor::fromRgb(45,64,79)));
        painter2.setPen(Qt::transparent);
        QRect rect = this->rect();
        rect.setWidth(rect.width() - 1);
        rect.setHeight(rect.height() - 1);
        painter2.drawRoundedRect(rect, 15, 15);
        //也可用QPainterPath 绘制代替 painter.drawRoundedRect(rect, 15, 15);
        {
            QPainterPath painterPath;
            painterPath.addRoundedRect(rect, 15, 15);
            painter2.drawPath(painterPath);
        }
        QWidget::paintEvent(event);
}

void createTable::mousePressEvent (QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = true;
        formerMainPos = this->pos();
        formerMousePos = event->globalPos();
    }

void createTable::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = false;
    }

void createTable::mouseMoveEvent ( QMouseEvent * event )
    {
        QPoint pos = event->globalPos();
        if (shouldMove)
        {
            int x = pos.x()-formerMousePos.x();
            int y = pos.y()-formerMousePos.y();
            move(formerMainPos.x()+x,formerMainPos.y()+y);
        }
    }

void createTable::shakeWindow(){
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


void createTable::setDBName(QString name){
    ui->dbName->setText(name);
}

void createTable::on_closeBut_clicked()
{
    this->close();
}

void createTable::on_pushButton_clicked()
{
    emit textChange(ui->dbName->text(),ui->tableName->text());
}
