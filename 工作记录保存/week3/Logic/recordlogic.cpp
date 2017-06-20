#include "recordlogic.h"

RecordLogic::RecordLogic()
{

}

bool RecordLogic::Insert(const QString strDBName, TableEntity &te, RecordEntity &re)
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
        if(t_dataOps.AlterTable(strTableFile,&te) == false)
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
