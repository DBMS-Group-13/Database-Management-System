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
    tabModel = new QStandardItemModel(ui->tableView);
    this->iniTab();
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

void createTable::iniTab(){
    tabModel->setHorizontalHeaderLabels(QStringList()<<"fie_name"<<"type"<<"prk"<<"nn"<<"un"<<"default");
    tabModel->setRowCount(1);
    tabModel->setItem(0,2,new QStandardItem("N"));
    tabModel->setItem(0,3,new QStandardItem("N"));
     tabModel->setItem(0,4,new QStandardItem("N"));
    ui->tableView->setModel(tabModel);
    for(int i = 0;i < 6;i++){
        if(i == 0 || i == 5){
            ui->tableView->setColumnWidth(i,250);
        }else{
            ui->tableView->setColumnWidth(i,100);
        }
    }
}

void createTable::setDBName(QString name){
    ui->dbName->setText(name);
}

void createTable::on_closeBut_clicked()
{
    this->close();
}

void createTable::setBeginPos(int size){
    this->beginPos = size;
}

void createTable::on_pushButton_clicked()
{
    emit textChange(ui->dbName->text(),ui->tableName->text());
    if(shouldChange == tabModel->rowCount()-1){
        if(isVaild == 1){
            isVaild = 0;
            this->shakeWindow();
            return;
        }
        if(beginPos == 0){
            beginPos = 1;
        }
        for(int i = this->beginPos-1;i < shouldChange;i++){
            ui->pBar->setMaximum(1);
            ui->pBar->value()+i/shouldChange;
            if(tabModel->item(i,5) == NULL){
                QString tmp = "NOD";
                emit fieldChange(ui->dbName->text(),ui->tableName->text(),tabModel->item(i,0)->text(),tabModel->item(i,1)->text(),tabModel->item(i,2)->text()
                                 ,tabModel->item(i,3)->text(),tabModel->item(i,4)->text(),tmp);
            }else{
                emit fieldChange(ui->dbName->text(),ui->tableName->text(),tabModel->item(i,0)->text(),tabModel->item(i,1)->text(),tabModel->item(i,2)->text()
                                 ,tabModel->item(i,3)->text(),tabModel->item(i,4)->text(),tabModel->item(i,5)->text());
            }
        }
    }else{
        this->shakeWindow();
        isVaild = 0;
    }
    this->close();
    //ui->progressBar->setValue(0);
}

void createTable::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(index.row()+1 == tabModel->rowCount()){
        tabModel->setItem(index.row()+1,2,new QStandardItem("N"));
        tabModel->setItem(index.row()+1,3,new QStandardItem("N"));
        tabModel->setItem(index.row()+1,4,new QStandardItem("N"));
        tabModel->setRowCount(index.row()+2);
    }
}

void createTable::on_tableView_clicked(const QModelIndex &index)
{
    shouldChange = 0;
    int row[15]={0};
    int prkNum = 0;
    if(tabModel->item(tabModel->rowCount()-2,1) == NULL)return;
    for(int i = 0;i < tabModel->rowCount()-1;i++){
        if(tabModel->item(i,1) == NULL)return;
        if(tabModel->item(i,1)->text() == "VARCHAR"||
                tabModel->item(i,1)->text() == "INT"||
                tabModel->item(i,1)->text() == "BOOL"||
                tabModel->item(i,1)->text() == "DOUBLE"||
                tabModel->item(i,1)->text() == "DATETIME"){
            tabModel->item(i,1)->setBackground(Qt::white);
            shouldChange++;
            continue;
        }
        tabModel->item(i,1)->setBackground(Qt::red);
        continue;
    }
    if(shouldChange == tabModel->rowCount()-1){
        if(shouldChange != 1){
        for(int i = 0;i < tabModel->rowCount()-1;i++){
            if(tabModel->item(i,2) != NULL){
                if(tabModel->item(i,2)->text() != "Y"){
                    tabModel->item(i,2)->setText("N");
                    tabModel->item(i,2)->setBackground(Qt::white);
                }else{
                    row[i] = 1;
                    prkNum++;
                }
            }
        }
        }
    }
    if(prkNum >1){
    for(int i = 0;i<15;i++){
        if(row[i] == 1){
            tabModel->item(i,2)->setBackground(Qt::red);
        }
    }
    shouldChange = 0;
    }
    if(prkNum==1){
        for(int i = 0;i <tabModel->rowCount()-1;i++){
            if(tabModel->item(i,2) != NULL){
                tabModel->item(i,2)->setBackground(Qt::white);
            }
        }
        for(int i = 0;i <tabModel->rowCount()-1;i++){
            if(tabModel->item(i,2)->text() == "Y"){
                tabModel->setItem(i,5,new QStandardItem("NOD"));
            }
        }
    }
    for(int i = 0;i < tabModel->rowCount()-2;i++){
        if(tabModel->item(i,4)->text() != "Y"){
            tabModel->item(i,4)->setText("N");
        }
    }
}

void createTable::on_flashButton_clicked()
{
    tabModel->clear();
    this->iniTab();
    ui->tableName->clear();
}

void createTable::reflashTable()
{
    tabModel->clear();
    this->iniTab();
    ui->tableName->clear();
}

void createTable::setTabName(QString name){
    ui->tableName->setText(name);
}
