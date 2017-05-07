#include "centerwindow.h"

centerwindow::centerwindow(QWidget *parent,QString userid) :
    QWidget(parent),
    ui(new Ui::centerwindow)
{
    ui->setupUi(this);
    user = userid;
    creTab = new createTable();
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    treeModel = new QStandardItemModel(ui->treeview);
    tabModel = new QStandardItemModel(ui->tableView);
    this->setMouseTracking(true);
    this->initStatus(userid);
    this->initTree(userid);
    ui->treeview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->treeview->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->setEditTriggers ( QAbstractItemView::NoEditTriggers);
    creDB = new createDB();
    ui->tableView->setAlternatingRowColors(true);
    connect(this,SIGNAL(customContextMenuRequested(const QPoint &)),this, SLOT(slotCustomContextMenu(const QPoint &)));
    connect(creDB,SIGNAL(textChange(QString)),this,SLOT(creDBTree(QString)));
    connect(creTab,SIGNAL(textChange(QString,QString)),this,SLOT(creDBChildTree(QString,QString)));
    //connect(creDB,SIGNAL(textChange2(QString,QString)),this,SLOT(creDBChildTree(QString,QString)));
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


void centerwindow::initTree(QString userid){
    treeModel->setHorizontalHeaderLabels(QStringList()<<userid);
    ui->treeview->setModel(treeModel);
}

void centerwindow::on_close_clicked()
{
    exit(0);
}

void centerwindow::on_creDBBut_clicked()
{
    creDB->show();
    qDebug()<<"93";
}

bool centerwindow::creDBTree(QString DBname){
    QList<QStandardItem*> list = treeModel->findItems(DBname);
    for(int i = 0;i < list.length();i++){
        if(list.at(i)->text() == DBname){
            creDB->shakeWindow();
            return false;
        }
    }
    treeModel->appendRow(new QStandardItem(DBname));
    ui->treeview->setModel(treeModel);
    return true;
}

bool  centerwindow::creDBChildTree(QString DBname, QString tableName){
    int i = 0;
    QList<QStandardItem*> list = treeModel->findItems(DBname);
    if(list.isEmpty()){
        creTab->shakeWindow();
        return false;
    }
    for(int i = 0;list.at(0)->child(i,0)!=NULL;i++){
        if(list.at(0)->child(i,0)->text() == tableName){
            creTab->shakeWindow();
            return false;
        }
    }
    for(i = 0;i < list.length();i++){
        if(list.at(i)->text() == DBname){
            break;
        }
    }
    treeModel->item(treeModel->indexFromItem(list.at(i)).row(),0)->appendRow(new QStandardItem(tableName));
    ui->treeview->setModel(treeModel);
    return true;
}

void centerwindow::on_addTableBut_clicked()
{

    creTab->show();
}

void centerwindow::on_treeview_clicked(const QModelIndex &index)
{
    if(index.parent().data().toString() == ""){
    selectDBName = index.data().toString();
    selectTableName = "";
    creTab->setDBName(selectDBName);
    ui->status->setText("主程序版本：1.0.0.0\t\tui版本：1.0.0.0\t\t用户:"+user+"\t\tDatabase:"+selectDBName);
    this->creTableWidgetDB();
    }else{
        selectDBName = index.parent().data().toString();
        selectTableName = index.data().toString();
        creTab->setDBName(selectDBName);
        ui->status->setText("主程序版本：1.0.0.0\t\tui版本：1.0.0.0\t\t用户:"+user+"\t\tDatabase:"+selectDBName+"\tTable:"+selectTableName);
        this->creTableWidget();
    }
    qDebug()<<selectDBName;
}

void centerwindow::on_delTableBut_clicked()
{
    if(selectTableName == "")return;
    else{
        QList<QStandardItem*> listDB = treeModel->findItems(selectDBName);
        for(int i = 0;treeModel->item(treeModel->indexFromItem(listDB.at(0)).row(),0)->child(i) != NULL;i++){
        if(treeModel->item(treeModel->indexFromItem(listDB.at(0)).row(),0)->child(i)->text()==selectTableName){
            treeModel->item(treeModel->indexFromItem(listDB.at(0)).row(),0)->removeRow(i);
        }
        }

    }
    ui->treeview->setModel(treeModel);
}

void centerwindow::creTableWidget(){
    tabModel->clear();
    tabModel->setHorizontalHeaderLabels(QStringList()<<"字段名称"<<"字段类型"<<"PR"<<"NULL"<<"default");
    tabModel->setItem(0,0,new QStandardItem("id"));
    tabModel->setItem(0,1,new QStandardItem("int"));
    tabModel->setItem(0,2,new QStandardItem("no"));
    tabModel->setItem(0,3,new QStandardItem("no"));
    tabModel->setItem(0,4,new QStandardItem(""));
    tabModel->setItem(1,0,new QStandardItem("sex"));
    tabModel->setItem(1,1,new QStandardItem("ENUM('男','女')"));
    tabModel->setItem(1,2,new QStandardItem("no"));
    tabModel->setItem(1,3,new QStandardItem("no"));
    tabModel->setItem(1,4,new QStandardItem("'男'"));
    tabModel->setItem(2,0,new QStandardItem("title"));
    tabModel->setItem(2,1,new QStandardItem("varchar()"));
    tabModel->setItem(2,2,new QStandardItem("no"));
    tabModel->setItem(2,3,new QStandardItem("no"));
    tabModel->setItem(2,4,new QStandardItem(""));
    ui->tableView->setModel(tabModel);
//    QStringList header;
//    ui->table = new QTableWidget(10,5);
//    header<<selectDBName<<"-"<<selectTableName;
//    ui->table->setHorizontalHeaderLabels(header);
//    ui->table->setItem(0,0,new QTableWidgetItem("Jan"));
//    ui->table->setItem(0,1,new QTableWidgetItem("Jan"));
//    ui->table->show();
}

void centerwindow::creTableWidgetDB(){
    tabModel->clear();
    tabModel->setHorizontalHeaderLabels(QStringList()<<"数据库名称"<<"创建者"<<"创建时间");
    tabModel->setItem(0,0,new QStandardItem(selectDBName));
    tabModel->setItem(0,1,new QStandardItem(user));
    tabModel->setItem(0,2,new QStandardItem("2017-05-07 21:26:26"));
    ui->tableView->setModel(tabModel);
}
