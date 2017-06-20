#include "recordwidget.h"
#include "ui_recordwidget.h"

RecordWidget::RecordWidget(QWidget *parent, QString DBName, QString TabName, QString PRK, QList<QString> UNList,QList<QString> NNList) :
    QWidget(parent),
    ui(new Ui::RecordWidget)
{
    ui->setupUi(this);
    this->DBName = DBName;
    this->TabName = TabName;
    this->PriKey = PRK;
    this->UN = UNList;
    this->NN = NNList;
    qDebug()<<UN;
    qDebug()<<NN;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowModality(Qt::ApplicationModal);
    tabModel = new QStandardItemModel(ui->tableView);
    if(tabModel->rowCount() == 0){
        tabModel->setRowCount(1);
    }else{
        tabModel->setRowCount(tabModel->rowCount()+1);
    }
    ui->nameLabel->setText("Tab_name:"+TabName);
}

RecordWidget::~RecordWidget()
{
    delete ui;
}

void RecordWidget::exec(){
    setAttribute(Qt::WA_ShowModal, true);
    show();
    QEventLoop loop;
    loop.exec();
}

void RecordWidget::paintEvent(QPaintEvent *event)
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

void RecordWidget::mousePressEvent (QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = true;
        formerMainPos = this->pos();
        formerMousePos = event->globalPos();
    }

void RecordWidget::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button()!=Qt::LeftButton) return;
        shouldMove = false;
    }

void RecordWidget::mouseMoveEvent ( QMouseEvent * event )
    {
        QPoint pos = event->globalPos();
        if (shouldMove)
        {
            int x = pos.x()-formerMousePos.x();
            int y = pos.y()-formerMousePos.y();
            move(formerMainPos.x()+x,formerMainPos.y()+y);
        }
    }

void RecordWidget::on_pushButton_clicked()
{
    delete(this);
}

void RecordWidget::reflash(){
    ui->tableView->setModel(tabModel);
}

void RecordWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(index.row() == tabModel->rowCount()-1){
        tabModel->setRowCount(tabModel->rowCount()+1);
    }
}

void RecordWidget::on_tableView_clicked(const QModelIndex &index)
{
        isValid = 0;
        if(this->PriKey != "NULL"){
            this->UN.append(this->PriKey);
        }
        if(this->UN.size() == 1){
            qDebug()<<"this->UN.size() == 1";
            return;
        }
        QList<int> coU;
        QHash<int,FieldEntity*>::const_iterator p;
        for(p = FNHash.constBegin();p != FNHash.constEnd();p++){
            if(this->UN.contains(p.value()->GetName())){
                coU.append(p.key());
            }
        }
        if(tabModel->rowCount() ==1){

        }else{
        for(int j = 0;j < coU.size();j++){
            QHash<int,QString> checkRepeat;
            QHash<int,int>redOrWhite;
            for(int cr = 0;cr < tabModel->rowCount()-1 ;cr++){
                if(tabModel->item(cr,coU.at(j)) == NULL){
                    tabModel->setItem(cr,coU.at(j),new QStandardItem(""));
                }
                checkRepeat.insert(cr,tabModel->item(cr,coU.at(j))->text());
            }
            qDebug()<<tabModel->rowCount()<<"A";
            for(int n = 0;n<checkRepeat.size();n++)
                redOrWhite.insert(n,0);
            for(int cr = 0;cr < redOrWhite.size();cr++){
                QString tmpCR = checkRepeat.value(cr);
                checkRepeat.remove(cr);
                if(redOrWhite.value(cr) == 0){
                for(int crd = cr + 1;crd < redOrWhite.size();crd++){
                    if(checkRepeat.value(crd) == tmpCR){
                        redOrWhite.remove(cr);
                        redOrWhite.insert(cr,1);
                        redOrWhite.remove(crd);
                        redOrWhite.insert(crd,1);
                        isValid = -1;
                    }
                }
                }
            }
            for(int num = 0;num < redOrWhite.size();num++){
                if(redOrWhite.value(num) == 1){
                    tabModel->item(num,coU.at(j))->setBackground(Qt::red);
                }
                if(redOrWhite.value(num) == 0){
                    tabModel->item(num,coU.at(j))->setBackground(Qt::white);
                }
            }
            redOrWhite.clear();

        }
        }
        for(int j = 0;j < tabModel->rowCount()-1;j++){
            for(int k = 0;k < FNHash.size();k++){
                if(tabModel->item(j,k) == NULL || tabModel->item(j,k)->text() == ""){
                    if(!FNHash.value(k)->getConstrArr().value(2).isEmpty())
                    tabModel->setItem(j,k,new QStandardItem(FNHash.value(k)->getConstrArr().value(2)));
                }
            }
        }
        for(int j = 0;j < tabModel->rowCount()-1;j++){
            for(int k = 0;k < FNHash.size();k++){
                if(NN.contains(FNHash.value(k)->GetName())){
                    if(tabModel->item(j,k) == NULL){
                        tabModel->setItem(j,k,new QStandardItem());
                    }
                    else if(tabModel->item(j,k)->text() == ""){
                        this->isValid = -1;
                        tabModel->item(j,k)->setBackground(Qt::red);
                    }else{
                        tabModel->item(j,k)->setBackground(Qt::white);
                    }
                }
            }
        }
    //    reflash();
    //    this->repaint();
}



void RecordWidget::on_applyButton_clicked()
{
    if(isValid == -1)return;
    RecordEntity *tmp = new RecordEntity[tabModel->rowCount()-1]();
    for(int i = 0;i < tabModel->rowCount()-1;i++){
        int count = 0;
        for(int j = 0;j < FNHash.size();j++){
            if(tabModel->item(i,j)->text() == "")count++;
            tmp[i].Put(FNHash.value(j)->GetName(),tabModel->item(i,j)->text());
            qDebug()<<FNHash.value(j)->GetName();
            qDebug()<<tabModel->item(i,j)->text();
        }
        if(count != FNHash.size())
            QR.insert(i,&tmp[i]);
        else
            QR.insert(i,NULL);
    }
    emit hahaha(QR);
    delete[] tmp;
}

