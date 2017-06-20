#include "centerwindow.h"

centerwindow::centerwindow(QWidget *parent,QString userid) :
    QWidget(parent),
    ui(new Ui::centerwindow)
{
    ui->setupUi(this);
    user = userid;
    mySer = new service();
    creTab = new createTable();
    creDB = new createDB();
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    treeModel = new QStandardItemModel(ui->treeview);
    tabModel = new QStandardItemModel(ui->tableView);
    this->setMouseTracking(true);
    this->initStatus(userid);
    this->initTree(userid);
    ui->treeview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setEditTriggers ( QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);
    ui->treeview->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(const QPoint &)),this, SLOT(customContextMenuRequested(QPoint)));
    connect(creDB,SIGNAL(textChange(QString)),this,SLOT(creDBTree(QString)));
    connect(creTab,SIGNAL(textChange(QString,QString)),this,SLOT(creDBChildTree(QString,QString)));
    connect(creTab,SIGNAL(fieldChange(QString,QString,QString,QString,QString,QString,QString,QString)),
            this,SLOT(creFieldEntity(QString,QString,QString,QString,QString,QString,QString,QString)));
}

centerwindow::~centerwindow()
{
    delete mySer;
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
    ui->status->setText(QStringLiteral("主程序版本:4.1.0.0\t\tui版本:2.0.0.0\t\t用户:")+userid);
}


void centerwindow::initTree(QString userid){
    treeModel->setHorizontalHeaderLabels(QStringList()<<userid);
    QHash<int,DBEntity *>::const_iterator i;
    for(i = mySer->getDBArr().constBegin();i != mySer->getDBArr().constEnd();++i){
        this->addDBTree(i.value()->GetName());
        mySer->SetCurDB(i.value()->GetName());
        DBEntity *tmp = i.value();
        QHash<int,TableEntity *>::const_iterator j;
        for(j = tmp->getTbArr().constBegin();j !=tmp->getTbArr().constEnd();++j){
        this->addTabTree(i.value()->GetName(),j.value()->GetName());
        }
        qDebug()<<i.value()->GetName();
    }
    //delete tmp;
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
    mySer->CreateDatabase(DBname);
    ui->treeview->setModel(treeModel);
    return true;
}

bool centerwindow::addDBTree(QString DBname){
    treeModel->appendRow(new QStandardItem(DBname));
    ui->treeview->setModel(treeModel);
    return true;
}

bool centerwindow::addTabTree(QString DBName, QString tableName){
    int i = 0;
    QList<QStandardItem*> list = treeModel->findItems(DBName);
    treeModel->item(treeModel->indexFromItem(list.at(i)).row(),0)->appendRow(new QStandardItem(tableName));
    ui->treeview->setModel(treeModel);
    return true;
}

bool  centerwindow::creDBChildTree(QString DBname, QString tableName){
    int i = 0;
    QList<QStandardItem*> list = treeModel->findItems(DBname);
    if(list.isEmpty()){
        creTab->shakeWindow();
        creTab->isVaild = 1;
        return false;
    }
    for(int i = 0;list.at(0)->child(i,0)!=NULL;i++){
        if(list.at(0)->child(i,0)->text() == tableName){
            //creTab->shakeWindow();
            return false;
        }
    }
    for(i = 0;i < list.length();i++){
        if(list.at(i)->text() == DBname){
            break;
        }
    }
    treeModel->item(treeModel->indexFromItem(list.at(i)).row(),0)->appendRow(new QStandardItem(tableName));
    mySer->CreateTable(DBname,tableName);
    ui->treeview->setModel(treeModel);
    return true;
}

void centerwindow::on_addTableBut_clicked()
{
    if(selectDBName == "newSql" && user == "root")return;
    creTab->reflashTable();
    if(selectTableName != ""){
        creTab->setTabName(selectTableName);
        mySer->SetCurDB(selectDBName);
        mySer->SetCurTable(selectTableName);
    for(int i = 0;i < mySer->GetCurTable()->m_arrFields.size();i++){
        creTab->tabModel->setItem(i,0,new QStandardItem(mySer->GetCurTable()->m_arrFields.value(i)->GetName()));
        creTab->tabModel->setItem(i,1,new QStandardItem(mySer->GetCurTable()
                                                        ->m_arrFields.value(i)->GetTypeName(mySer->GetCurTable()
                                                                                            ->m_arrFields.value(i)->GetDataType())));
        if(mySer->GetCurTable()->m_arrFields.value(i)->m_arrconstr.value(0) == "null"){
            creTab->tabModel->setItem(i,2,new QStandardItem("Y"));
        }else{
            creTab->tabModel->setItem(i,2,new QStandardItem("N"));
        }
        if(mySer->GetCurTable()->m_arrFields.value(i)->m_arrconstr.value(1) == "null"){
            creTab->tabModel->setItem(i,3,new QStandardItem("Y"));
        }else{
            creTab->tabModel->setItem(i,3,new QStandardItem("N"));
        }
        if(mySer->GetCurTable()->m_arrFields.value(i)->m_arrconstr.value(2).isNull()){
            creTab->tabModel->setItem(i,5,new QStandardItem("NOD"));
        }else{
            creTab->tabModel->setItem(i,5,new QStandardItem(mySer->GetCurTable()->m_arrFields.value(i)->m_arrconstr.value(2)));
        }
        if(mySer->GetCurTable()->m_arrFields.value(i)->m_arrconstr.value(3) == "null"){
            creTab->tabModel->setItem(i,4,new QStandardItem("Y"));
        }else{
            creTab->tabModel->setItem(i,4,new QStandardItem("N"));
        }
    }
    }
    creTab->show();
}

void centerwindow::on_treeview_clicked(const QModelIndex &index)
{
    if(index.parent().data().toString() == ""){
    selectDBName = index.data().toString();
    selectTableName = "";
    creTab->setDBName(selectDBName);
    ui->status->setText(QStringLiteral("主程序版本:4.1.0.0\t\tui版本:2.0.0.0\t\t用户:")+
                        user+QStringLiteral("\t\tDatabase:")+selectDBName);
    this->creTableWidgetDB();
    }else{
        selectDBName = index.parent().data().toString();
        selectTableName = index.data().toString();
        creTab->setDBName(selectDBName);
        ui->status->setText(QStringLiteral("主程序版本:4.1.0.0\t\tui版本:2.0.0.0\t\t用户:")+
                            user+"\t\tDatabase:"+selectDBName+"\tTable:"+selectTableName);
        this->creTableWidget();
    }
    qDebug()<<selectDBName;
}

void centerwindow::on_delTableBut_clicked()
{
    qDebug()<<"edde";
    if(selectTableName == "")return;
    else if(user == "root" && selectDBName == "newSql")return;
    else{
        QList<QStandardItem*> listDB = treeModel->findItems(selectDBName);
        for(int i = 0;treeModel->item(treeModel->indexFromItem(listDB.at(0)).row(),0)->child(i) != NULL;i++){
        if(treeModel->item(treeModel->indexFromItem(listDB.at(0)).row(),0)->child(i)->text()==selectTableName){
            treeModel->item(treeModel->indexFromItem(listDB.at(0)).row(),0)->removeRow(i);
            mySer->DeleteTable(selectTableName,selectDBName);
            tabModel->clear();
        }
        }

    }
    ui->treeview->setModel(treeModel);
    selectTableName = "";
}

void centerwindow::creTableWidget(){
    tabModel->clear();
    tabModel->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("字段名称")
                                        <<QStringLiteral("字段类型")
                                        <<"default"
                                        <<"cre_time"
                                        <<"M_time");
    mySer->SetCurDB(selectDBName);
    qDebug()<<selectDBName;
    mySer->SetCurTable(selectTableName);
    qDebug()<<selectTableName;
    TableEntity *tmpTab = mySer->GetCurTable();
    for(int i = 0;i < tmpTab->GetFieldNum();++i){
        FieldEntity *tmpFd = tmpTab->GetFieldAt(i);
        tabModel->setItem(i,0,new QStandardItem(tmpFd->GetName()));
        tabModel->setItem(i,1,new QStandardItem(tmpFd->GetTypeName(tmpFd->GetDataType())));
        tabModel->setItem(i,2,new QStandardItem(tmpFd->getConstrArr().value(2)));
        tabModel->setItem(i,3,new QStandardItem(tmpTab->GetCrTime().toString()));
        tabModel->setItem(i,4,new QStandardItem(tmpFd->GetMTime().toString()));
    }
    tmpTab = NULL;
    delete tmpTab;
    ui->tableView->setModel(tabModel);
    for(int i = 0;i<4;i++){
        ui->tableView->setColumnWidth(i,300);
    }
}

void centerwindow::creTableWidgetDB(){
    tabModel->clear();
    mySer->SetCurDB(selectDBName);
    DBEntity *tmpEntity = mySer->GetCurDB();
    tabModel->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("数据库名称")
                                        <<"create_time"
                                        <<"PATH");
    tabModel->setItem(0,0,new QStandardItem(tmpEntity->GetName()));
    tabModel->setItem(0,1,new QStandardItem(tmpEntity->GetCtTime().toString()));
    tabModel->setItem(0,2,new QStandardItem(tmpEntity->GetFilepath()));
    ui->tableView->setModel(tabModel);
    for(int i = 0;i<3;i++){
        ui->tableView->setColumnWidth(i,300);
    }
    tmpEntity = NULL;
    delete tmpEntity;
}

void centerwindow::on_dropDBBut_clicked()
{
    if(selectTableName != "" || selectDBName == ""){
        return;
    }else if(this->user == "root" && selectDBName == "newSql"){
        return;
    }
    else{
        QList<QStandardItem*> listDB = treeModel->findItems(selectDBName);
        treeModel->removeRow(listDB.at(0)->row());
        mySer->DeleteDatabase(selectDBName);
        tabModel->clear();
    }
    ui->treeview->setModel(treeModel);
}

bool centerwindow::creFieldEntity(QString DB, QString TAB, QString FN, QString TP, QString PR, QString NN, QString UN, QString def){
//    enum DataType
//    {
//        DT_NONE = 0,
//        DT_INTEGER = 1,// Integer: 4byte  corresponding: int
//        DT_BOOL = 2,// Boolean: 1byte, corresponding：bool
//        DT_DOUBLE = 3,// Floating-point number: 2byte,  corresponding: double
//        DT_VARCHAR = 4,// String: 256byte, corresponding: char256]
//        DT_DATETIME = 5// Data time: 16byte, corresponding: SYSTEMTIME type
//    };
    if(TP == "INT"){
        FieldEntity *tmpFE = new FieldEntity(FN,1,0,0);
        if(PR == "Y"){
            QString tmp = "null";
            tmpFE->m_arrconstr.insert(0,tmp);
            tmpFE->SetParam(1);
        }
        if(NN == "Y"){
            QString tmp = "null";
            tmpFE->m_arrconstr.insert(1,tmp);
        }
        if(def != "NOD"){
            tmpFE->m_arrconstr.insert(2,def);
        }
        if(UN == "Y"){
            tmpFE->SetParam(1);
            QString tmp = "nul";
            tmpFE->m_arrconstr.insert(3,tmp);
        }
        if(!mySer->checkFDName(DB,TAB,FN)){
            mySer->ModifyField(TAB,DB,FN,tmpFE);
        }else{
        mySer->AddField(DB,TAB,*tmpFE);
        }
        delete tmpFE;
    }else if(TP == "BOOL"){
        FieldEntity *tmpFE = new FieldEntity(FN,2,NULL,0);
        if(PR == "Y"){
            tmpFE->SetParam(1);
            QString tmp = "null";
            tmpFE->m_arrconstr.insert(0,tmp);
        }
        if(NN == "Y"){
            QString tmp = "null";
            tmpFE->m_arrconstr.insert(1,tmp);
        }
        if(def != "NOD"){
            tmpFE->m_arrconstr.insert(2,def);
        }
        if(UN == "Y"){
            tmpFE->SetParam(1);
            QString tmp = "nul";
            tmpFE->m_arrconstr.insert(3,tmp);
        }
        if(!mySer->checkFDName(DB,TAB,FN)){
            mySer->ModifyField(TAB,DB,FN,tmpFE);
        }else{
        mySer->AddField(DB,TAB,*tmpFE);
        }
        delete tmpFE;
    }else if(TP == "DOUBLE"){
        FieldEntity *tmpFE = new FieldEntity(FN,3,NULL,0);
        if(PR == "Y"){
            tmpFE->SetParam(1);
            QString tmp = "null";
            tmpFE->m_arrconstr.insert(0,tmp);
        }
        if(NN == "Y"){
            QString tmp = "null";
            tmpFE->m_arrconstr.insert(1,tmp);
        }
        if(def != "NOD"){
            tmpFE->m_arrconstr.insert(2,def);
        }
        if(UN == "Y"){
            tmpFE->SetParam(1);
            QString tmp = "nul";
            tmpFE->m_arrconstr.insert(3,tmp);
        }
        if(!mySer->checkFDName(DB,TAB,FN)){
            mySer->ModifyField(TAB,DB,FN,tmpFE);
        }else{
        mySer->AddField(DB,TAB,*tmpFE);
        }
        delete tmpFE;
    }else if(TP == "VARCHAR"){
        FieldEntity *tmpFE = new FieldEntity(FN,4,NULL,0);
        if(PR == "Y"){
            tmpFE->SetParam(1);
            QString tmp = "null";
            tmpFE->m_arrconstr.insert(0,tmp);
        }
        if(NN == "Y"){
            QString tmp = "null";
            tmpFE->m_arrconstr.insert(1,tmp);
        }
        if(def != "NOD"){
            tmpFE->m_arrconstr.insert(2,def);
        }
        if(UN == "Y"){
            tmpFE->SetParam(1);
            QString tmp = "nul";
            tmpFE->m_arrconstr.insert(3,tmp);
        }
        if(!mySer->checkFDName(DB,TAB,FN)){
            mySer->ModifyField(TAB,DB,FN,tmpFE);
        }else{
        mySer->AddField(DB,TAB,*tmpFE);
        }
        delete tmpFE;
    }else if(TP == "DATETIME"){
        FieldEntity *tmpFE = new FieldEntity(FN,5,NULL,0);
        if(PR == "Y"){
            tmpFE->SetParam(1);
            QString tmp = "null";
            tmpFE->m_arrconstr.insert(0,tmp);
        }
        if(NN == "Y"){
            QString tmp = "null";
            tmpFE->m_arrconstr.insert(1,tmp);
        }
        if(def != "NOD"){
            tmpFE->m_arrconstr.insert(2,def);
        }
        if(UN == "Y"){
            tmpFE->SetParam(1);
            QString tmp = "nul";
            tmpFE->m_arrconstr.insert(3,tmp);
        }
        if(!mySer->checkFDName(DB,TAB,FN)){
            mySer->ModifyField(TAB,DB,FN,tmpFE);
        }else{
        mySer->AddField(DB,TAB,*tmpFE);
        }
        delete tmpFE;
    }else{
        return false;
    }
    mySer->CleanContainer();
     mySer->LoadAllInfo();
    return true;
}

void centerwindow::on_treeview_doubleClicked()
{
    if(selectTableName == "")return;
    rw = new RecordWidget(0,selectDBName,selectTableName,mySer->getPri(selectDBName,selectTableName),mySer->getUN(selectDBName,selectTableName),mySer->getNN(selectDBName,selectTableName));
    mySer->SetCurDB(selectDBName);
    mySer->SetCurTable(selectTableName);
    mySer->LoadRecord(selectDBName,selectTableName);
//    int recordNum = mySer->GetRecordNum();
    TableEntity *tmpTab = mySer->GetCurTable();
    QHash<int,FieldEntity*>::const_iterator i;
    QStringList header;
    for(int i = 0;i<mySer->GetCurTable()->m_arrFields.size();i++){
        header<<mySer->GetCurTable()->m_arrFields.value(i)->GetName();
        QHash<int, RecordEntity*>::const_iterator j;
        for(j = mySer->getRecordArr().constBegin();j != mySer->getRecordArr().constEnd();j++){
            rw->tabModel->setItem(j.key(),i,new QStandardItem(j.value()->getReArr().value(mySer->GetCurTable()->m_arrFields.value(i)->GetName())));
        }
    }
    rw->tabModel->setItem(mySer->getRecordArr().size(),mySer->GetCurTable()->m_arrFields.size()-1,new QStandardItem());
    rw->tabModel->setHorizontalHeaderLabels(header);
    rw->reflash();
    rw->FNHash = mySer->GetCurTable()->m_arrFields;
    connect(rw,SIGNAL(hahaha(QHash<int,RecordEntity*>)),this,SLOT(changeRecord(QHash<int,RecordEntity*>)));
    rw->exec();
}

//MENU
void centerwindow::on_treeview_customContextMenuRequested(const QPoint &pos){
    qDebug()<<"on_treeView_customContextMenuRequested";
    QModelIndex index=ui->treeview->currentIndex();
    QString filename = ui->treeview->model()->data(index).toString();
    QList<QStandardItem*> list = treeModel->findItems(filename);
    if(!list.isEmpty()){
        selectDBName = filename;
        QMenu *menu =new QMenu();
        menu->addAction(QString("Rename"),this,SLOT(showRenameWid()));
        menu->exec(QCursor::pos());
        delete menu;
        ui->status->setText(QStringLiteral("主程序版本:4.1.0.0\t\tui版本:2.0.0.0\t\t用户:")+
                            user+QStringLiteral("\t\tDatabase:")+selectDBName);
        return;
    }
    selectDBName = index.parent().data().toString();
    selectTableName = filename;
    ui->status->setText(QStringLiteral("主程序版本:4.1.0.0\t\tui版本:2.0.0.0\t\t用户:")+
                        user+"\t\tDatabase:"+selectDBName+"\tTable:"+selectTableName);
    QMenu *menu =new QMenu();
//    menu->addAction(QString("Insert"),this,SLOT(callRec(selectDBName,selectTableName)));
    menu->addAction(QString("Del"),this,SLOT(on_delTableBut_clicked()));
    menu->addAction(QString("Rename"),this,SLOT(showRenameWid()));
    menu->exec(QCursor::pos());
    delete menu;
}

void centerwindow::on_tableView_customContextMenuRequested(const QPoint &pos){
    QMenu *menu = new QMenu();
    QString filename = ui->tableView->currentIndex().data().toString();
    if(!mySer->checkFDName(selectDBName,selectTableName,filename)){
        this->tn = filename;
        menu->addAction(QString("del"),this,SLOT(delField()));
        menu->addAction(QString("rename"),this,SLOT(showRenameWid()));
        menu->exec(QCursor::pos());
    }
    qDebug()<<"hahah";
    delete menu;
}

void centerwindow::deleteField(QString name){
    qDebug()<<"void centerwindow::deleteField(QString name){";
    if(name == selectDBName)return;
    if(user == "root" && selectDBName == "newSql")return;
    mySer->SetCurDB(selectTableName);
    mySer->SetCurTable(selectTableName);
    mySer->DeleteField(selectTableName,selectDBName,name);
}

void centerwindow::changeRecord(QHash<int, RecordEntity*> QR){
    mySer->cleanRecordArr();
    mySer->getQR(QR);
    mySer->changeRecordToFile(this->selectDBName,this->selectTableName);
}

void centerwindow::showRenameWid(){
     rnWindow *rn = new rnWindow();
    connect(rn,SIGNAL(emlit(QString)),this,SLOT(rename(QString)));
    rn->exec();
    delete rn;
}

void centerwindow::delField()
{
    if(!mySer->checkFDName(selectDBName,selectTableName,tn)){
        this->deleteField(tn);
        this->creTableWidget();
    }
}

void centerwindow::rename(QString name){
    if(selectTableName == ""){
        if(mySer->checkDBName(selectDBName)){
            mySer->RenameDatabase(selectDBName,name);
            selectDBName = name;
            this->treeModel->clear();
            this->initTree(user);
        }
    }else if(selectTableName != ""){
        if(!mySer->checkTBName(selectDBName,selectTableName)){
        mySer->ReNameTable(selectDBName,selectTableName,name);
        selectTableName = name;
        this->treeModel->clear();
        this->initTree(user);
        }else{
            mySer->ModifyField(selectTableName,selectDBName,tn,name);
            this->creTableWidget();
        }
    }
}

//void centerwindow::callRec(QString sb, QString st){
//    mySer->SetCurDB(sb);
//    mySer->SetCurTable(st);
//    TableEntity *tmptb =mySer->GetCurTable();

//}
