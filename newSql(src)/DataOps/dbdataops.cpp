#include "dbdataops.h"
#include "./Global/ref.h"
#include "./Logic/filelogic.h"


DBDataOps::DBDataOps()
{

}

/**
 * @brief DBDataOps::Create
 * @param strFilepath
 * @param db
 * @param bAppend 是否追加写入文件，若true，追加写入；若false，则清除文件内容从头写入
 * @return
 */
bool DBDataOps::Create(const QString strFilepath, DBEntity db, bool bAppend)
{
    char* c_CtTime;
    try
        {
            QFile file(strFilepath);
            if(bAppend == true)
            {
                if (file.open(QIODevice::Append|QIODevice::WriteOnly) == FALSE)
                {
                    return false;
                }
            }
            else
            {
                if (file.open(QIODevice::Truncate|QIODevice::WriteOnly) == FALSE)
                {
                    return false;
                }
            }
            QDataStream out(&file);
            c_CtTime=new char[256];
            DatabaseBlock DBlock=db.GetBlock();

            strcpy(c_CtTime,DBlock.crtimAe.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
            out<<DBlock.name<<DBlock.type<<DBlock.filepath<<c_CtTime;

            delete c_CtTime;  //释放动态内存
            file.close();
            return true;
        }
        catch(AppException e)// Catch exceptions
        {
            delete c_CtTime;  //释放动态内存
            // Delete the exception information

            // Throw a custom exception
            //throw new AppException(_T("Failed to create the database file!"));
        }
        return false;
}

bool DBDataOps::GetDatabase(const QString strFilepath,DBARR &arrDB)
{
    char* p;
    try
        {
            // 只读模式打开文件
            QFile file(strFilepath);
            if (file.open(QIODevice::ReadOnly) == FALSE)
            {
                return false;
            }

            // Read the database information
            bool bExist = false;
            DatabaseBlock DBlock;
            p=new char[256];
            QDataStream in(&file);

            int n = 0;
            while (!in.atEnd())
            {
                DBEntity *db = new DBEntity();
                in>>p;
                strcpy(DBlock.name,p);
                in>>DBlock.type;
                in>>p;
                strcpy(DBlock.filepath,p);
                in>>p;
                DBlock.crtimAe=QDateTime::fromString(QString(p),"yyyy-MM-dd hh:mm:ss");
                db->SetBlock(DBlock);
                arrDB.insert(n,db);
                n++;
            }
            file.close();

            delete p;  //释放动态内存
            return bExist;
        }
        catch(AppException* e)// Catch exceptions
        {
            delete p;  //释放动态内存
        }
        return false;
}



bool DBDataOps::ReName(DBEntity& olddb, DBEntity& newdb,DBARR &arrDB)
    {
    //修改数据库文件夹名称
    QString tb_oldfile=olddb.GetFilepath().append("/").append(olddb.GetName()).append(".tb");
    QString tb_newfile=olddb.GetFilepath().append("/").append(newdb.GetName()).append(".tb");
    QFile f(tb_oldfile);
    //文件重命名用相对路径
    f.rename(tb_oldfile,tb_newfile);
    FileLogic fl;
    QDir qdir(olddb.GetFilepath());
    //文件夹重命名用绝对路径
    qdir.rename(fl.GetAbsolutePath(olddb.GetFilepath()),fl.GetAbsolutePath(newdb.GetFilepath()));


    //修改.db描述文件
    QFile file(fl.GetDBFile());
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QDataStream out(&file);
    char *p=new char[256];
    for(int i=0;i<arrDB.size();i++)
    {
        DBEntity *db=arrDB.value(i);
        memcpy(p,db->GetCtTime().toString("yyyy-MM-dd hh:mm:ss").toLatin1().data(),256);
        DatabaseBlock DBlock=db->GetBlock();
        out<<DBlock.name<<DBlock.type<<DBlock.filepath<<p;
    }
    delete p;
    file.close();
    return true;
}



/**
 * @brief DBDataOps::DeleteDB
 * @param DBDirepath 数据库文件夹
 * @param dbFilepath .db文件路径
 * @param arrDB
 * @return
 */
bool DBDataOps::DeleteDB(const QString DBDirepath,const QString dbFilepath, DBARR &arrDB)
{
    //删除数据库文件夹
    FileLogic fl;
    fl.DeleteDirectory(DBDirepath);

    //修改.db文件
    QFile file(dbFilepath);
    file.open(QIODevice::Truncate|QIODevice::WriteOnly);
    QDataStream out(&file);

    char *c_CtTime=new char[256];
    for(int i=0;i<arrDB.size();i++)
    {
        DBEntity* db=arrDB.value(i);
        if(db!=NULL)
        {
            DatabaseBlock DBlock=db->GetBlock();
            strcpy(c_CtTime,DBlock.crtimAe.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
            out<<DBlock.name<<DBlock.type<<DBlock.filepath<<c_CtTime;
        }
    }
    file.close();
    return true;
}
