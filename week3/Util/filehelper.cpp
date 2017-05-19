#include "filehelper.h"
#include "appexception.h"
#include<QFile>
#include<QDir>
#include<excpt.h>
#include<QCoreApplication>
// 创建文件,QString 为文件相对路径
bool FileHelper::CreateNewFile(const QString strFileName)
{
   try
    {
        QDir *dir = new QDir;
        // 创建文件夹
        for (int i = 0; i < strFileName.length(); i++)
        {
            if ( ('\\' == strFileName.at(i)
                || '/' == strFileName.at(i))
                && 2 != i
                )
            {
                if(!dir->exists(strFileName.left(i)))
                {
                  if(!dir->mkdir(strFileName.left(i)))
                      return false;
                }

            }
        }
        delete dir;
        // 创建文件
        QFile file(strFileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            return false;
        }
        file.close();

        return true;
    }
    catch (QString e)
    {
        printf(e.toStdString().data());
        throw new AppException(e);
    }

    return false;
}
// 检测文件是否存在，QString为文件相对路径
bool FileHelper::IsValidFile(const QString strPath){
    try
    {
        QFile file(strPath);
        if (file.open(QIODevice::ReadOnly))
        {
            file.close();
            return true;
        }
    }
    catch (QString e)
    {
        throw new AppException(e);
    }
    return false;
}

bool FileHelper::IsValidFolder(const QString strPath){
    try
    {
        QDir *dir = new QDir;
        if(!dir->exists(strPath))
                return false;
        delete dir;
        return true;
    }
    catch (QString e)
    {
        throw new AppException(e);
    }
    return false;
}

