#include "tablelogic.h"

TableLogic::TableLogic()
{

}

bool TableLogic::CreateTable(const QString strDBName, TableEntity &te)
{
    try
    {
        // 判断文件是否存在，如果不存在则创建
        QString strTableFolder = (fileLogic.GetDBFolder(strDBName)+"/%1").arg(te.GetName());
        QString strTableFile = fileLogic.GetTableFile(strDBName);
        if (FileHelper::IsValidFolder(strTableFolder) == true)
        {
            return false;
        }
        if(FileHelper::IsValidFile(strTableFile) == false)
        {
            if(FileHelper::CreateNewFile(strTableFile) == false)
            {
            return false;
            }
        }
        QString strTdfPath = fileLogic.GetTbDefineFile(strDBName, te.GetName());
        QString strTrdPath = fileLogic.GetTbRecordFile(strDBName, te.GetName());
        if(FileHelper::CreateNewFile(strTdfPath) == false)
        {
            return false;
        }
        if(FileHelper::CreateNewFile(strTrdPath) == false)
        {
            return false;
        }
        // 设置表定义文件路径
        te.SetTdfPath(strTdfPath);
        // 设置表记录文件路径
        te.SetTrdPath(strTrdPath);

        // 创建表并且保存表信息
        if(t_dataOps.Create(strTableFile, &te) == false)
        {
            return false;
        }

        return true;
    }
    catch (AppException* e)
    {
        throw e;
    }

    return false;
}

bool TableLogic::AddField(const QString strDBName, TableEntity &te, FieldEntity &fe)
{
    try
    {
        // 判断文件是否存在，如果不存在则创建
        QString strTdfPath = te.GetTdfPath();
        if (FileHelper::IsValidFile(strTdfPath) == false)
        {
            if(FileHelper::CreateNewFile(strTdfPath) == false)
            {
                return false;
            }
        }

        // 保存字段信息
        if(t_dataOps.AddField(strTdfPath, &fe) == false)
        {
            return false;
        }
        // 添加字段
        te.AddField(fe);


        // 更新修改时间
        QDateTime tTime = QDateTime::currentDateTime();
        te.SetMTime(tTime);

        // 修改表信息
        QString strTableFile = fileLogic.GetTableFile(strDBName);
        if(t_dataOps.AlterTable(strTableFile, &te) == false)
        {
            return false;
        }
        return true;
    }
    catch (AppException* e)
    {
        throw e;
    }

    return false;
}

int TableLogic::GetTables(const QString strDBName, TABLEARR &arrTables)
{
    int nCount = 0;

    try
    {
        // 获取表描述文件
        QString strTableFile = fileLogic.GetTableFile(strDBName);

        // 查询表信息
        nCount = t_dataOps.GetTables(strTableFile, &arrTables);

        // 从表结构文件中一条条地读取表结构信息
        QHash<int,TableEntity *>::const_iterator i;
        for(i = arrTables.constBegin();i != arrTables.constEnd();++i){
            t_dataOps.GetFields(i.value()->GetTdfPath(), i.value());
        }
    }
    catch (AppException e)
    {
        throw e;
    }

    return nCount;
}
