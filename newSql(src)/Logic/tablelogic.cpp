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
        QString strTicPath = fileLogic.GetTbConstrFile(strDBName, te.GetName());
        if(FileHelper::CreateNewFile(strTdfPath) == false)
        {
            return false;
        }
        if(FileHelper::CreateNewFile(strTrdPath) == false)
        {
            return false;
        }
        if(FileHelper::CreateNewFile(strTicPath) == false)
        {
            return false;
        }
        // 设置表定义文件路径
        te.SetTdfPath(strTdfPath);
        // 设置表记录文件路径
        te.SetTrdPath(strTrdPath);
        // 设置表约束文件路径
        te.SetTicPath(strTicPath);
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

bool TableLogic::AddField(const QString strDBName, TableEntity &te, FieldEntity &fe,TABLEARR &tba)
{
    try
    {
        // 判断文件是否存在，如果不存在则创建
        QString strTdfPath = te.GetTdfPath();
        QString strTicPath = te.GetTicPath();
        if (FileHelper::IsValidFile(strTdfPath) == false)
        {
            if(FileHelper::CreateNewFile(strTdfPath) == false)
            {
                return false;
            }
        }

        if (FileHelper::IsValidFile(strTicPath) == false)
        {
            if(FileHelper::CreateNewFile(strTicPath) == false)
            {
                return false;
            }
        }

        // 保存字段信息
        if(t_dataOps.AddField(strTdfPath, &fe) == false)
        {
            return false;
        }
        if(t_dataOps.AddConstr(strTicPath,&fe) == false){
            return false;
        }

        // 添加字段
        te.AddField(fe);
        // 更新修改时间
        QDateTime tTime = QDateTime::currentDateTime();
        te.SetMTime(tTime);

        // 修改表信息
        QString strTableFile = fileLogic.GetTableFile(strDBName);
        if(t_dataOps.AlterTable(strTableFile, tba) == false)
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
            t_dataOps.GetConstr(i.value()->GetTicPath(),i.value());
        }
    }
    catch (AppException e)
    {
        throw e;
    }

    return nCount;
}

bool TableLogic::deleteTable(const QString tbName,const QString dbName, TABLEARR &arrTables){
    QHash<int,TableEntity *>::const_iterator i;
    for(i = arrTables.constBegin();i != arrTables.constEnd();++i){
        if (QString::compare(i.value()->GetName(),tbName,Qt::CaseInsensitive) == 0)
        {
            QString TBFilepath = fileLogic.GetTableFile(dbName);
            QString TBDirepath = QString("./DBMS_ROOT/data/%1/%2").arg(dbName,tbName);
            delete i.value();
            (TableEntity *)(i.value()) = NULL;
            if(t_dataOps.delTable(arrTables,TBFilepath,TBDirepath))
                return true;
            else
                return false;
        }
    }
    return false;
}

bool TableLogic::deleteField(const QString dbName,const QString fieldName,TableEntity *te,RECORDARR &arrRe){
    QHash<int,FieldEntity *>::const_iterator i;
    for(i = te->m_arrFields.constBegin();i != te->m_arrFields.constEnd();++i){
        if (QString::compare(i.value()->GetName(),fieldName,Qt::CaseInsensitive) == 0)
        {
            int n = i.value()->GetParam();
            QString name = i.value()->GetName();
            delete i.value();
            (FieldEntity *)(i.value()) = NULL;
            if(t_dataOps.delField(name,n,fileLogic.GetTableFile(dbName),te,arrRe))
            {
                t_dataOps.ModifyConstr(te->GetTicPath(),te);
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

bool TableLogic::alterField(FieldEntity *oldfe,TableEntity *te,FieldEntity *newfe){
    if(t_dataOps.AlterField(te,*oldfe,*newfe))
        if(t_dataOps.ModifyConstr(te->GetTicPath(),te))
            return true;
    return false;
}

bool TableLogic::alterTableName(QString DBName,QString TBName,TableEntity * tbe,TABLEARR &tba){
    QString strTdfPath = fileLogic.GetTbDefineFile(DBName, tbe->GetName());
    QString strTrdPath = fileLogic.GetTbRecordFile(DBName, tbe->GetName());
    QString strTicPath = fileLogic.GetTbConstrFile(DBName, tbe->GetName());
    // 设置表定义文件路径
    tbe->SetTdfPath(strTdfPath);
    // 设置表记录文件路径
    tbe->SetTrdPath(strTrdPath);
    // 设置表约束文件路径
    tbe->SetTicPath(strTicPath);
    // 设置修改时间
    tbe->SetMTime(QDateTime::currentDateTime());
    if(t_dataOps.AlterTableName(fileLogic.GetTableFile(DBName),fileLogic.GetDBFolder(DBName)+QString("/%1").arg(TBName),tbe,tba))
        return true;
    return false;
}
