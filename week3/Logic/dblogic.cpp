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
        if (FileHelper::IsValidFolder("./DBMS_ROOT/data/"+db.GetName()))
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
bool DBLogic::RenameDatabase(DBEntity &oldDb,DBEntity &newDb){
    return DB_Ops.ReName(oldDb,newDb);
}
