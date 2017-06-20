#include "centerwindow.h"
#include "QMouseEvent"
#include "qmath.h"
#include "QDebug"
#include "qpainter.h"
#include "ui_centerwindow.h"
#include "QStandardItem"

centerwindow::centerwindow(QWidget *parent,QString userid) :
    QWidget(parent),
    ui(new Ui::centerwindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMouseTracking(true);
    this->initStatus(userid);
    this->initTree();
}

centerwindow::~centerwindow()
{
    delete ui;
}

void centerwindow::mousePressEvent (QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = true;
        formerMainPos = this->pos();
        formerMousePos = event->globalPos();
    }

void centerwindow::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = false;
    }

void centerwindow::mouseMoveEvent ( QMouseEvent * event )
    {
        QPoint pos = event->globalPos();
        if (shouldMove)
        {
            int x = pos.x()-formerMousePos.x();
            int y = pos.y()-formerMousePos.y();
            move(formerMainPos.x()+x,formerMainPos.y()+y);
        }
    }

void centerwindow::paintEvent(QPaintEvent *event)
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

void centerwindow::initStatus(QString userid){
    ui->status->setText("主程序版本：1.0.0.0\t\tui版本：1.0.0.0\t\t用户:"+userid);
}


void centerwindow::initTree(){
    QStandardItemModel *model = new QStandardItemModel(ui->treeview);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Project")<<QStringLiteral("Info"));
    ui->treeview->setModel(model);
}

void centerwindow::on_close_clicked()
{
    exit(0);
}
