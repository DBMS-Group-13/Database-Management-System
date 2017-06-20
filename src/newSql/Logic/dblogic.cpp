#include "dblogic.h"
#include "./Util/filehelper.h"
DBLogic::DBLogic()
{

}

/**************************************************
[FunctionName]	CreateDatabase
[Function]	Create database
[Argument]	CDBEntity &db: Database entity object, contains the name of the database.
[ReturnedValue]	bool: True if the operation is successful, other false.
**************************************************/
bool DBLogic::CreateDatabase(DBEntity &db)
{
    try
    {
        // Decide whether the file exists, if there is no,a file will be created.
        QString strDBFile = fileLogic.GetDBFile();
        if (FileHelper::IsValidFile(strDBFile) == false)
        {
            if(FileHelper::CreateNewFile(strDBFile) == false)
            {
                return false;
            }
        }

        // Read file, decide whether exists the database of the same name
        if (FileHelper::IsValidFolder(FileLogic::getUser()+"/DBMS_ROOT/data/"+db.GetName()))
        {
            return false;
        }


        // Create database
        QString strDBFolder = fileLogic.GetDBFolder(db.GetName());
        db.SetFilepath(strDBFolder);
        if(DB_Ops.Create(strDBFile, db) == false)
        {
            return false;
        }
    }
    catch (AppException* e)
    {
        throw e;
    }
    return true;
}

/**************************************************
[FunctionName]	GetDatabase
[Function]	Query the database information
[Argument]	CDBEntity &db: Database entity object, contains the name of the database.
        Queried database information will be saved to the object.
[ReturnedValue]	bool: True if exists the database of the same name, otherwise false
**************************************************/
bool DBLogic::GetDatabases(DBARR &m_arrDB)
{
    try
    {
        QString strDBFile = fileLogic.GetDBFile();
        return DB_Ops.GetDatabase(strDBFile,m_arrDB);
    }
    catch (AppException* e)
    {
        throw e;
    }

    return false;
}

bool DBLogic::RenameDatabase(QString newDbName,DBEntity * db,DBARR& m_arrDB){
    DBEntity oldDb(db->GetBlock());
    db->SetName(newDbName);
    QString strDBFolder = fileLogic.GetDBFolder(db->GetName());
    db->SetFilepath(strDBFolder);
    if(DB_Ops.ReName(oldDb,*db,m_arrDB)){
        QHash<int,TableEntity *>::const_iterator i;
        for(i = db->getTbArr().constBegin();i != db->getTbArr().constEnd();++i){
        QString strTdfPath = fileLogic.GetTbDefineFile(db->GetName(), i.value()->GetName());
        QString strTrdPath = fileLogic.GetTbRecordFile(db->GetName(), i.value()->GetName());
        QString strTicPath = fileLogic.GetTbConstrFile(db->GetName(), i.value()->GetName());
        // 设置表定义文件路径
        i.value()->SetTdfPath(strTdfPath);
        // 设置表记录文件路径
        i.value()->SetTrdPath(strTrdPath);
        // 设置表约束文件路径
        i.value()->SetTicPath(strTicPath);
        if(!TB_Ops.AlterTable(fileLogic.GetTableFile(db->GetName()),db->getTbArr())){
            return false;
        }
        }
        return true;
    }
    return false;
}

bool DBLogic::DeleteDatabase(QString dbName,DBARR &arrdb){
    QHash<int,DBEntity *>::const_iterator i;
    for(i = arrdb.constBegin();i != arrdb.constEnd();++i){
        if (QString::compare(i.value()->GetName(),dbName,Qt::CaseInsensitive) == 0)
        {
            QString DBDirepath = i.value()->GetFilepath();
            QString dbFilepath = fileLogic.GetDBFile();
            delete i.value();
            (DBEntity *)(i.value()) = NULL;
            if(DB_Ops.DeleteDB(DBDirepath,dbFilepath,arrdb))
                return true;
            else
                return false;
        }
    }
    return false;
}
