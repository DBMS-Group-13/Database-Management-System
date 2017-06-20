#include "createdb.h"
#include "qpropertyanimation.h"

createDB::createDB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::createDB)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QRegExp regExp("[_a-zA-Z0-9]+$");
    ui->dbName->setValidator(new QRegExpValidator(regExp, ui->dbName));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowModality(Qt::ApplicationModal);
}

createDB::~createDB()
{
    delete ui;
}

void createDB::paintEvent(QPaintEvent *event)
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

void createDB::mousePressEvent (QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = true;
        formerMainPos = this->pos();
        formerMousePos = event->globalPos();
    }

void createDB::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = false;
    }

void createDB::mouseMoveEvent ( QMouseEvent * event )
    {
        QPoint pos = event->globalPos();
        if (shouldMove)
        {
            int x = pos.x()-formerMousePos.x();
            int y = pos.y()-formerMousePos.y();
            move(formerMainPos.x()+x,formerMainPos.y()+y);
        }
    }

void createDB::shakeWindow(){
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

void createDB::on_closeBut_clicked()
{
    this->close();
}

void createDB::on_pushButton_clicked()
{
    if(!ui->dbName->text().isEmpty()){
        emit textChange(ui->dbName->text());
        //emit textChange2(ui->dbName->text(),ui->dbName->text());
        this->close();
    }
}
