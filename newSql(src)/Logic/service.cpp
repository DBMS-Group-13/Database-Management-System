#include "service.h"
#include "tablelogic.h"
#include "recordlogic.h"
#include"dblogic.h"
service::service()
{
    m_strError = ("");	//	Initialize the exception information
    m_dbEntity = NULL;	// The default database is info
    m_tbEntity = NULL;
    LoadAllInfo();
}

service::~service()
{
    CleanContainer();
}
QString service::GetError()
{
    //	Remove white space characters
    m_strError.trimmed();
    return m_strError;
}

void service::SetError(QString strError)
{
    m_strError = strError;
}
void service::CleanContainer(){
    // Get the number of elements in the db array.
    QHash<int,DBEntity *>::const_iterator i;
    for(i = m_arrDB.constBegin();i != m_arrDB.constEnd();++i){
        if(i.value()!=NULL){
            delete i.value();
            (DBEntity *)(i.value()) = NULL;
        }
    }
    // Empty db array
    m_arrDB.clear();

   // Get the number of elements in the record array.
    QHash<int,RecordEntity *>::const_iterator j;
    for(j = m_arrRecord.constBegin();j != m_arrRecord.constEnd();++j){
        if(j.value()!=NULL){
            RecordEntity* del =  (RecordEntity*) j.value();
            delete del;
            (RecordEntity*)(j.value()) = NULL;
        }
    }
/*    for(int j = 0;j<m_arrRecord.size();i++)
    {
        if(m_arrRecord.value(j) != NULL){
            delete m_arrRecord.value(j);
          //  m_arrRecord.value(j) = NULL;
        }
    }*/
    // Empty record array
    m_arrRecord.clear();
}

void service::LoadAllInfo(){
    DBLogic dbl;
    try
    {
        dbl.GetDatabases(m_arrDB);
        QHash<int,DBEntity *>::const_iterator i;
        for(i = m_arrDB.constBegin();i != m_arrDB.constEnd();++i){
            LoadTables(i.value());
        }
    }
    catch (AppException* e)	// Catch custom exception
    {
        // Throw exception
        m_strError = e->GetErrorMessage();
        delete e;
    }
}

void service::SetCurDB(QString strDBName)
{
    if (strDBName.length() > 0)
    {
        QHash<int,DBEntity *>::const_iterator i;
        for(i = m_arrDB.constBegin();i != m_arrDB.constEnd();++i){
            if (QString::compare(i.value()->GetName(),strDBName,Qt::CaseInsensitive) == 0)
            {
                m_dbEntity = i.value();
                return;
            }
        }
    }
    else
    {
        m_dbEntity = NULL;
    }
}

bool service::CreateDatabase(QString dbname){
    DatabaseBlock db;
    db.type = "true";
    db.crtimAe = QDateTime::currentDateTime ();
    strcpy(db.name,dbname.toLatin1().data());
    DBEntity* dbe = new DBEntity(db);
    DBLogic dbl;
    if(dbl.CreateDatabase(*dbe)){
        int n = m_arrDB.size();
        m_arrDB.insert(n,dbe);
        return true;
    }
    delete dbe;
    return false;
}

bool service::RenameDatabase(QString oldDBname,QString newDBname){
    if (newDBname.length() > 0)
    {
        QHash<int,DBEntity *>::const_iterator i;
        for(i = m_arrDB.constBegin();i != m_arrDB.constEnd();++i){
            if (QString::compare(i.value()->GetName(),oldDBname,Qt::CaseInsensitive) == 0)
            {
                DBLogic dbl;
                dbl.RenameDatabase(newDBname,i.value(),m_arrDB);
                return true;
            }
        }
    }
    return false;
}

bool service::DeleteDatabase(QString dbName){
    if (dbName.length() > 0)
    {
        DBLogic dbl;
        if(dbl.DeleteDatabase(dbName,m_arrDB)){
            CleanContainer();
            LoadAllInfo();
            return true;
        }
    }
    return false;
}

TableEntity* service::CreateTable(QString strDBName,QString strName)
{
    SetCurDB(strDBName);
    TableEntity* pTable = new TableEntity();
    pTable->SetName(strName);
    TableLogic tbLogic;
    try
    {
        // Decide whether creates table successfully
        if (tbLogic.CreateTable(m_dbEntity->GetName(), *pTable) == true)
        {
            // If creates table successfully, the created table information would be saved to the array.
            int n = m_dbEntity->getTbArr().size();
            m_dbEntity->getTbArr().insert(n,pTable);
        }
        else
        {
            // If creates failure, release the memory allocated by new
            delete pTable;
            pTable = NULL;
        }
    }
    catch(AppException *e)	// Catch exception
    {
        // If there is exception, release the memory allocated by new
        if (pTable != NULL)
        {
            delete pTable;
            pTable = NULL;
        }
        // Get exception information
        m_strError = e->GetErrorMessage();
        // Delete exception
        delete e;
    }

    return pTable;
}

void service::SetCurTable(QString strTableName)
{
    if (strTableName.length() > 0)
    {
        QHash<int,TableEntity *>::const_iterator i;
        for(i = m_dbEntity->getTbArr().constBegin();i != m_dbEntity->getTbArr().constEnd();++i){
            if (QString::compare(i.value()->GetName(),strTableName,Qt::CaseInsensitive) == 0)
            {
                m_tbEntity = i.value();
                return;
            }
        }
    }
    else
    {
        m_tbEntity = NULL;
    }
}

TableEntity* service::GetTable(int nIndex)
{
    return m_dbEntity->getTbArr().value(nIndex);
}

bool service::DeleteTable(QString tbName,QString DBname){
    if (DBname.length() > 0 && tbName.length() > 0)
    {
        QHash<int,DBEntity *>::const_iterator i;
        for(i = m_arrDB.constBegin();i != m_arrDB.constEnd();++i){
            if (QString::compare(i.value()->GetName(),DBname,Qt::CaseInsensitive) == 0)
            {
                TableLogic tbl;
                if(tbl.deleteTable(tbName,DBname,i.value()->getTbArr())){
                    CleanContainer();
                    LoadAllInfo();
                    return true;
                }
                else
                    return false;
            }
        }
    }
    return false;
}

bool service::ReNameTable(QString DBName,QString oldName,QString newName){
    SetCurDB(DBName);
    TableLogic tbl;
    QHash<int,TableEntity *>::const_iterator i;
    for(i = m_dbEntity->getTbArr().constBegin();i != m_dbEntity->getTbArr().constEnd();++i){
        if(QString::compare(i.value()->GetName(),oldName,Qt::CaseInsensitive) == 0){
            i.value()->SetName(newName);
            if(tbl.alterTableName(DBName,oldName,i.value(),m_dbEntity->getTbArr()))
                return true;
            else{
                i.value()->SetName(oldName);
                return false;
            }
        }
    }
    return false;
}

void service::LoadTables(DBEntity* db)
{
    TableLogic tbLogic;

    try
    {
        // Get the number of table in the table array
        QHash<int,TableEntity *>::const_iterator i;
        for(i = db->getTbArr().constBegin();i != db->getTbArr().constEnd();++i){
            if(i.value()!=NULL){
                delete i.value();
                (TableEntity *)(i.value()) = NULL;
            }
        }

        // Empty array
        db->getTbArr().clear();

        // Get table information
        tbLogic.GetTables(db->GetName(), db->getTbArr());
    }
    catch(AppException* e)
    {
        m_strError = e->GetErrorMessage();
        delete e;
    }
}

FieldEntity* service::AddField(QString strDBName,QString strTBName,FieldEntity &field)
{
    SetCurDB(strDBName);
    SetCurTable(strTBName);
    TableLogic tbLogic;
    try
    {
        // Add a field
        if(tbLogic.AddField(m_dbEntity->GetName(), *m_tbEntity, field,m_dbEntity->getTbArr()) == false)
        {
            return NULL;
        }

        // Get field number
        int nCount = m_tbEntity->GetFieldNum();

        // Return the last field
        FieldEntity* pField = m_tbEntity->GetFieldAt(nCount -1);
        return pField;
    }
    catch(AppException* e)
    {
        m_strError = e->GetErrorMessage();
        delete e;
        return NULL;
    }
    return NULL;
}
bool service::DeleteField(QString tbName,QString DBname,QString fieldName){
    if (DBname.length() > 0 && tbName.length() > 0 && fieldName.length() > 0)
    {
        QHash<int,DBEntity *>::const_iterator i;
        for(i = m_arrDB.constBegin();i != m_arrDB.constEnd();++i){
            if (QString::compare(i.value()->GetName(),DBname,Qt::CaseInsensitive) == 0)
            {
                QHash<int,TableEntity *>::const_iterator j;
                for(j = i.value()->getTbArr().constBegin();j != i.value()->getTbArr().constEnd();++j){
                    if (QString::compare(j.value()->GetName(),tbName,Qt::CaseInsensitive) == 0){
                        TableLogic tbl;
                        LoadRecord(DBname,tbName);
                        if(tbl.deleteField(DBname,fieldName,j.value(),m_arrRecord)){
                            CleanContainer();
                            LoadAllInfo();
                            return true;
                        }
                        else
                            return false;
                    }
                }
            }
        }
    }
    return false;
}

bool service::ModifyField(QString tbName,QString DBname,QString fieldName,FieldEntity* newField){
    SetCurDB(DBname);
    SetCurTable(tbName);
    QHash<int,FieldEntity *>::const_iterator i;
    for(i = m_tbEntity->m_arrFields.constBegin();i != m_tbEntity->m_arrFields.constEnd();++i){
        if (QString::compare(i.value()->GetName(),fieldName,Qt::CaseInsensitive) == 0){
           TableLogic tbl;
           FieldEntity* oldField = new FieldEntity();
           oldField->SetBlock(i.value()->GetBlock());
           oldField->m_arrconstr = i.value()->m_arrconstr;
           i.value()->SetBlock(newField->GetBlock());
           i.value()->m_arrconstr = newField->m_arrconstr;
           if(tbl.alterField(oldField,m_tbEntity,i.value()))
               return true;
           else
               return false;
        }
    }
    return false;
}

bool service::ModifyField(QString tbName,QString DBname,QString fieldName,QString newName){
    SetCurDB(DBname);
    SetCurTable(tbName);
    QHash<int,FieldEntity *>::const_iterator i;
    for(i = m_tbEntity->m_arrFields.constBegin();i != m_tbEntity->m_arrFields.constEnd();++i){
         if (QString::compare(i.value()->GetName(),fieldName,Qt::CaseInsensitive) == 0){
             TableLogic tbl;
             FieldEntity* oldField = new FieldEntity();
             oldField->SetBlock(i.value()->GetBlock());
             oldField->m_arrconstr = i.value()->m_arrconstr;
             i.value()->SetName(newName);
             if(tbl.alterField(oldField,m_tbEntity,i.value()))
                 return true;
             else
                 return false;
         }
    }
        return false;
}

RecordEntity* service::InsertRecord(QString strDBName,QString strTBName,RecordEntity &record)
{
    RecordLogic recordLogic;
    RecordEntity* pRecord = new RecordEntity(record);
    SetCurDB(strDBName);
    SetCurTable(strTBName);
    try
    {
        // Insert record
        if (recordLogic.Insert(m_dbEntity->GetName(), *m_tbEntity, record,m_dbEntity->getTbArr()) == true)
        {
            // Save the record which is added successfully to the record array.
            int n = m_arrRecord.size();
            m_arrRecord.insert(n,pRecord);
            return pRecord;
        }
    }
    catch (AppException* e)
    {
        if (pRecord != NULL)
        {
            delete pRecord;
            pRecord = NULL;
        }
        m_strError = e->GetErrorMessage();
        delete e;
    }

    return NULL;
}

int service::GetRecordNum()
{
    return m_arrRecord.size();
}

RecordEntity* service::GetRecord(int nIndex)
{
    return (RecordEntity*)m_arrRecord.value(nIndex);
}

void service::LoadRecord(QString strDBName,QString strTBName)
{
     cleanRecordArr();
     SetCurDB(strDBName);
     SetCurTable(strTBName);
     try
     {
        RecordLogic recordLogic;
        // Decide whether get record successfully
        if (recordLogic.SelectAll(*m_tbEntity, m_arrRecord) == false)
        {
            // If exists record, empty it
            if(m_arrRecord.size() > 0)
            {
                QHash<int,RecordEntity *>::const_iterator j;
                for(j = m_arrRecord.constBegin();j != m_arrRecord.constEnd();++j){
                    if(j.value()!=NULL){
                        delete j.value();
                        (RecordEntity*)(j.value()) = NULL;
                    }
                }
                m_arrRecord.clear();
            }
        }
    }
    catch (AppException* e)
    {
        // If there is exception, save exception information and delete the exception object
        m_strError = e->GetErrorMessage();
        delete e;
    }
}

bool service::queryOne(QString DBName,QString TBName,SEARCHARRAY search_arr){
    cleanRecordArr();
    SetCurDB(DBName);
    SetCurTable(TBName);
    RecordLogic rl;
    if(rl.Select(search_arr,*m_tbEntity,m_arrRecord))
        return true;
    return false;
}

void service::cleanRecordArr(){
    // Get the number of elements in the record array.
    try{
        QHash<int,RecordEntity *>::const_iterator j;
     for(j = m_arrRecord.constBegin();j != m_arrRecord.constEnd();++j){
         if(j.value()!=NULL){
             delete (RecordEntity*) j.value();
             (RecordEntity*)(j.value()) = NULL;
         }
     }
     // Empty record array
     m_arrRecord.clear();}
    catch(QString s){
        m_arrRecord.clear();
    }
}

QHash<int, DBEntity *> & service::getDBArr(){
    return m_arrDB;
}

QHash<int,RecordEntity *> & service::getRecordArr(){
    return m_arrRecord;
}

bool service::changeRecordToFile(QString DBName, QString TBName){
    try{
        SetCurDB(DBName);
        SetCurTable(TBName);
        RecordLogic rdl;
        rdl.modifyRecord(DBName,*m_tbEntity,m_arrRecord);
        return true;
    }
    catch (AppException* e)
    {
        // If there is exception, save exception information and delete the exception object
        m_strError = e->GetErrorMessage();
        delete e;
    }
    return false;
}

QString service::getPri(QString DBName,QString TBName){
    SetCurDB(DBName);
    SetCurTable(TBName);
    QHash<int,FieldEntity *>::const_iterator i;
    for(i = m_tbEntity->m_arrFields.constBegin();i != m_tbEntity->m_arrFields.constEnd();++i){
        QHash<int,QString>::const_iterator j;
        for(j = i.value()->getConstrArr().constBegin();j != i.value()->getConstrArr().constEnd();++j){
            if(j.key() == 0)
                return i.value()->GetName();
        }
    }
    return NULL;
}

bool service::checkDBName(QString DBName){
    // Get the number of elements in the db array.
    QHash<int,DBEntity *>::const_iterator i;
    for(i = m_arrDB.constBegin();i != m_arrDB.constEnd();++i){
        if (QString::compare(i.value()->GetName(),DBName,Qt::CaseInsensitive) == 0){
            return true;
        }
    }
    return false;
}
bool service::checkTBName(QString DBName,QString TBName){
    SetCurDB(DBName);
    QHash<int,TableEntity *>::const_iterator i;
    for(i = m_dbEntity->getTbArr().constBegin();i != m_dbEntity->getTbArr().constEnd();++i){
        if (QString::compare(i.value()->GetName(),TBName,Qt::CaseInsensitive) == 0){
            return false;
        }
    }
    return true;
}

bool service::checkFDName(QString DBName,QString TBName,QString FDName){
    SetCurDB(DBName);
    SetCurTable(TBName);
    if( m_tbEntity->m_arrFields.size() !=0){
    QHash<int,FieldEntity *>::const_iterator i;
    for(i = m_tbEntity->m_arrFields.constBegin();i != m_tbEntity->m_arrFields.constEnd();++i){
        if (QString::compare(i.value()->GetName(),FDName,Qt::CaseInsensitive) == 0){
            return false;
        }
    }
    }
    return true;
}

DBEntity* service::GetCurDB(){
    return m_dbEntity;
}

TableEntity *service::GetCurTable(){
    return m_tbEntity;
}

QList<QString> service::getUN(QString DBName,QString TBName){
    SetCurDB(DBName);
    SetCurTable(TBName);
    QList<QString> ql;
    QHash<int,FieldEntity *>::const_iterator i;
    for(i = m_tbEntity->m_arrFields.constBegin();i != m_tbEntity->m_arrFields.constEnd();++i){
        qDebug()<<i.value()->getConstrArr().value(3);
        if(!i.value()->getConstrArr().value(3).isEmpty()){
        ql.append(i.value()->GetName());
        }
    }
    return ql;
}

QList<QString> service::getNN(QString DBName,QString TBName){
    SetCurDB(DBName);
    SetCurTable(TBName);
    QList<QString> ql;
    QHash<int,FieldEntity *>::const_iterator i;
    for(i = m_tbEntity->m_arrFields.constBegin();i != m_tbEntity->m_arrFields.constEnd();++i){
        qDebug()<<i.value()->getConstrArr().value(1);
        if(!i.value()->getConstrArr().value(1).isEmpty()){
        ql.append(i.value()->GetName());
        }
    }
    return ql;
}
void service::getQR(QHash<int,RecordEntity *> QR){
    int count = 0;
    for(int i = 0;i<QR.size();i++){
        if(QR.value(i) != NULL){
            RecordEntity * re = new RecordEntity();
            re->m_mapData = QR.value(i)->m_mapData;
            this->m_arrRecord.insert(count,re);
            count++;
        }
    }
}
