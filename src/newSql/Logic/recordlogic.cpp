#include "recordlogic.h"

RecordLogic::RecordLogic()
{

}

bool RecordLogic::Insert(const QString strDBName, TableEntity &te, RecordEntity &re,TABLEARR& tba)
{
    try
    {
        // 判断文件是否存在，不存在则创建
        QString strTrdPath = te.GetTrdPath();
        if (FileHelper::IsValidFile(strTrdPath) == false)
        {
            if(FileHelper::CreateNewFile(strTrdPath) == false)
            {
                return false;
            }
        }

        // 插入一条记录
        if (r_dataOps.Insert(te, re) == false)
        {
            return false;
        }

        // 修改记录数
        int nRecordNum = te.GetRecordNum()+1;
        te.SetRecordNum(nRecordNum);

        // 修改表信息
        QString strTableFile = fileLogic.GetTableFile(strDBName);
        if(t_dataOps.AlterTable(strTableFile,tba) == false)
        {
            return false;
        }

        return true;
    }
    catch (AppException *e)
    {
        throw e;
    }

    return false;
}

bool RecordLogic::SelectAll(TableEntity &te, RECORDARR &data)
{
    try
    {
        // 读取记录
        if (r_dataOps.SelectAll(te, data) == false)
        {
            return false;
        }

        return true;
    }
    catch (AppException *e)
    {
        throw e;
    }

    return false;
}

bool RecordLogic::Select(SEARCHARRAY search_arr,TableEntity &te, RECORDARR &reArr)
{

    try
    {
        QHashIterator<int,QString> it(search_arr);
        //有索引
        while(it.hasNext())
        {
             it.next();
             int key=it.key();
             QString value=it.value();
             if(te.GetFieldAt(key)->GetParam()!=0)
             {
                 RecordEntity *re=new RecordEntity();
                 if(r_dataOps.SelectOne(*(te.GetFieldAt(key)),value,te,*re))
                 {
                     if(r_dataOps.Compare(search_arr,te,*re))
                     {
                         reArr.insert(0,re);
                         return true;
                     }
                     else return false;
                 }
                 else return false;
             }
        }

        //无索引
        r_dataOps.Select(search_arr,te, reArr);

        return true;
    }
    catch (AppException *e)
    {
        throw e;
    }

    return false;
}

bool RecordLogic::modifyRecord(QString dbName,TableEntity &te,RECORDARR &data){
    try{
        te.SetRecordNum(data.size());
        te.SetMTime(QDateTime::currentDateTime());
        r_dataOps.ModifyAndDelete(fileLogic.GetTableFile(dbName),te,data);
        return true;
    }
    catch(AppException *e){
        throw e;
    }
    return false;
}

