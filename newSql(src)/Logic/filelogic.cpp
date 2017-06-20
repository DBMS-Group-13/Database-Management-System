#include "filelogic.h"

QString FileLogic::username = "";

/**************************************************
[FunctionName]	GetDBFile
[Function]	Get the path of the database file: ruanko.db file
[Argument]	void
[ReturnedValue]	CString: "ruanko.db",file's absolute path
**************************************************/
QString FileLogic::GetDBFile(void)
{
    QString strPath = ("");
    try
    {
        // Get absolute path of ruanko.db file
        strPath = username+"/DBMS_ROOT/info.db";
    }
    catch (AppException* e)
    {
        throw e;
    }
    return strPath;
}

/**************************************************
[FunctionName]	GetDBFolder
[Function]	Get the path of the database folder
[Argument]	const CString strDBName: Database name
[ReturnedValue]	CString: Absolute path of the database folder
**************************************************/
QString FileLogic::GetDBFolder(const QString strDBName)
{
    QString strFolder;
    try
    {
        // Get the path of the database folder
        strFolder=username+QString("/DBMS_ROOT/data/%1").arg(strDBName);
    }
    catch (AppException* e)
    {
        throw e;
    }
    catch (...)
    {
        throw new AppException("Failed to get the path of the database folder!");
    }

    return strFolder;
}

/**************************************************
[FunctionName]	GetTableFile
[Function]	Get the path of the database table description file
[Argument]	const CString strDBName: Database name
[ReturnedValue]	CString: Absolute path of the database table description file
**************************************************/
QString FileLogic::GetTableFile(const QString strDBName)
{
    QString strPath;
    try
    {
        // Get the absolute path of the table description file(*.tb)
        strPath=username+QString("/DBMS_ROOT/data/%1/%2.tb").arg(strDBName, strDBName);
    }
    catch (AppException* e)
    {
        throw e;
    }
    catch (...)
    {
        throw new AppException("Failed to get tb file path!");
    }
    return strPath;
}

/**************************************************
[FunctionName]	GetTbDefineFile
[Function]	Get the path of the table definition file
[Argument]	const CString strDBName: Database name
        const CString strTableName: Table name
[ReturnedValue]	CString: Absolute path of the table definition file
**************************************************/
QString FileLogic::GetTbDefineFile(const QString strDBName, const QString strTableName)
{
    QString strPath;
    try
    {
        strPath=username+QString("/DBMS_ROOT/data/%1/%2/%3.tdf").arg(strDBName, strTableName,strTableName);
    }
    catch (AppException* e)
    {
        throw e;
    }
    catch (...)
    {
        throw new AppException("Failed to get the path of the table definition file");
    }

    return strPath;
}

/**************************************************
[FunctionName]	GetTbRecordFile
[Function]	Get the path of the table record file
[Argument]	const CString strDBName: Database name
        const CString strTableName: Table name
[ReturnedValue]	CString: Absolute path of the record file
**************************************************/
QString FileLogic::GetTbRecordFile(const QString strDBName, const QString strTableName)
{
    QString strPath = _T("");
    try
    {
        strPath=username+QString("/DBMS_ROOT/data/%1/%2/%3.trd").arg(strDBName, strTableName,strTableName);
    }
    catch (AppException* e)
    {
        throw e;
    }
    catch (...)
    {
        throw new AppException("Failed to get the path of the table record file!");
    }

    return strPath;
}

QString FileLogic::GetTbConstrFile(const QString strDBName, const QString strTableName)
{
    QString strPath = _T("");
    try
    {
        strPath=username+QString("/DBMS_ROOT/data/%1/%2/%3.tic").arg(strDBName, strTableName,strTableName);
    }
    catch (AppException* e)
    {
        throw e;
    }
    catch (...)
    {
        throw new AppException("Failed to get the path of the table record file!");
    }

    return strPath;
}
/************************************************************************
[FunctionName]	GetAbsolutePath
[Function]	Change relative path into an absolute path.
[Argument]	CString：Relative paths(relative executable file in folder)
[ReturnedValue]	CString：Absolute path
************************************************************************/
QString FileLogic::GetAbsolutePath(const QString strRelativePath)
{
    QString strFolder;
    QDir qDir;
    strFolder=qDir.absoluteFilePath(strRelativePath);
    return strFolder;
}

/*
 * 遍历文件夹逐个删除文件。返回true表示文件夹不存在或被成功删除。
 */
bool FileLogic::DeleteDirectory(const QString &path)
{
    if (path.isEmpty())
        return false;

    QDir dir(path);
    if(!dir.exists())
        return true;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            DeleteDirectory(fi.absoluteFilePath());
    }
    return dir.rmpath(dir.absolutePath());
}

void FileLogic::setUser(QString name){
    username = "./";
    username = username+name;
}

QString FileLogic:: getUser(){
    return username;
}
