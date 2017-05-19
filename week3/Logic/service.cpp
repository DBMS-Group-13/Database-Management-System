#include "service.h"
#include "tablelogic.h"
#include "recordlogic.h"
#include"dblogic.h"
service::service()
{
    m_strError = ("");	//	Initialize the exception information
    m_dbEntity = NULL;	// The default database is info
    m_tbEntity = NULL;
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

service::~service()
{

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
            delete j.value();
            (RecordEntity*)(j.value()) = NULL;
        }
    }
    // Empty record array
    m_arrRecord.clear();
}

DBEntity* service::GetDBEntity()
{
    return m_dbEntity;
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

DBEntity* service::CreateDatabase(QString dbname){
    DatabaseBlock db;
    db.type = "true";
    db.crtimAe = QDateTime::currentDateTime ();
    strcpy(db.name,dbname.toLatin1().data());
    DBEntity* dbe = new DBEntity(db);
    DBLogic dbl;
    if(dbl.CreateDatabase(*dbe)){
        int n = m_arrDB.size();
        m_arrDB.insert(n,dbe);
        return dbe;
    }
    delete dbe;
    return NULL;
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
            int n = m_arrTable.size();
            m_dbEntity->getTbArr().insert(n+1,pTable);
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

TableEntity* service::GetCurTable(){
    return m_tbEntity;
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

int service::GetTableNum()
{
    return m_dbEntity->getTbArr().size();
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
        if(tbLogic.AddField(m_dbEntity->GetName(), *m_tbEntity, field) == false)
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

RecordEntity* service::InsertRecord(QString strDBName,QString strTBName,RecordEntity &record)
{
    RecordLogic recordLogic;
    RecordEntity* pRecord = new RecordEntity(record);
    SetCurDB(strDBName);
    SetCurTable(strTBName);
    try
    {
        // Insert record
        if (recordLogic.Insert(m_dbEntity->GetName(), *m_tbEntity, record) == true)
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

    // Get the number of elements in the record array.
     QHash<int,RecordEntity *>::const_iterator j;
     for(j = m_arrRecord.constBegin();j != m_arrRecord.constEnd();++j){
         if(j.value()!=NULL){
             delete j.value();
             (RecordEntity*)(j.value()) = NULL;
         }
     }
     // Empty record array
     m_arrRecord.clear();

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


