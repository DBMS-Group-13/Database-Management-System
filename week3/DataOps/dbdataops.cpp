#include "dbdataops.h"
#include "./Global/ref.h"


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
