#include "Recorddataops.h"
#include "./Logic/filelogic.h"

RecordDataOps::RecordDataOps()
{

}
/**************************************************
[FunctionName]	Insert
[Function]	Create new rows in a table
[Argument]	CTableEntity &te: Table structure information
        CRecordEntity &re: Record information entity
[ReturnedValue]	bool: True if the operation is successful; otherwise false.
**************************************************/
bool RecordDataOps::Insert(TableEntity &te, RecordEntity &re)
{
    try
        {
            QFile file(te.GetTrdPath());   //打开文件
            QTextStream out(&file);
            if (file.open(QIODevice ::WriteOnly|QIODevice::Append) == FALSE)
            {
                return false;
            }
            //out.seek(file.size());  //光标指向文尾

            qint64 pos=out.device()->pos();
            // Save record
            Write(out, &te, &re);

            // Close file
            file.close();

            /**
              * 维护index
              */
            for(int i=0;i<te.GetFieldNum();i++)
            {
                FieldEntity *fe=te.GetFieldAt(i);
                if(fe->GetParam()!=0) //判断是否为索引
                {
                    QFileInfo fileinfo(te.GetTdfPath());
                    QString ixFilePath=QString("%1/%2.ix").arg(fileinfo.path(),fe->GetName());
                    QFile ixFile(ixFilePath);
                    QDataStream ixout(&ixFile);
                    ixFile.open(QIODevice::Append|QIODevice::WriteOnly);
                    switch(fe->GetDataType())
                    {
                    case 1:  //int
                    {
                        int data=re.Get(fe->GetName()).toInt(&ok,10);
                        ixout<<data;
                        ixout<<pos;
                        break;
                    }
                    case 3:  //double
                    {
                        double data=re.Get(fe->GetName()).toDouble(&ok);
                        ixout<<data;
                        ixout<<pos;
                        break;
                    }
                    case 4:  //varchar
                    {
                        char* data=new char[256];
                        memcpy(data,re.Get(fe->GetName()).toLatin1().data(),256);
                        ixout<<data;
                        ixout<<pos;
                        delete data;
                        break;
                    }
                    default:
                        break;
                    }
                    ixFile.close();
                }
            }

            return true;
        }
        catch (QException e)
        {
            throw new AppException(QString::fromLocal8Bit ("Failed to save record!"));
        }

        return false;
}
/**************************************************
[FunctionName]	SelectAll
[Function]	Retrieve all records from a specified table
[Argument]	CTableEntity &te: Table structure information
        RECORDARR &data: Recordset
[ReturnedValue]	int: The total number of the records
**************************************************/
int RecordDataOps::SelectAll(TableEntity &te, RECORDARR &data)
{
    try
        {
            QFile file(te.GetTrdPath());
            QTextStream in(&file);
            // Open file
            if (file.open(QIODevice ::ReadOnly) == FALSE)
            {
                return 0;
            }
            file.seek(0);//光标指向最开始的位置

            int nCount = 0;
            while (!in.atEnd())
            {
                // Get the value to write
                RecordEntity* pRecordEntity = new RecordEntity();
                if (Read(in, te, *pRecordEntity) == true)  //将所有记录读出来，插入到QHash中
                {
                    data.insert(nCount,pRecordEntity);
                    nCount++;
                }
                else
                {
                    delete pRecordEntity;
                    pRecordEntity = NULL;
                    break;// Exit the while loop
                }
            }
            // Close file
            file.close();

            return nCount;
        }
        catch (QException e)
        {
            throw new AppException(QString::fromLocal8Bit ("Failed to query record!"));
        }

        return 0;
}
/**************************************************
[FunctionName]	Write
[Function]	To save a record to a file
[Argument]	CFile &file: Open file of data record
        CTableEntity &te: Table structure information
        CRecordEntity &re: Record information entity
[ReturnedValue]	bool: True if the operation is successful;otherwise false.
**************************************************/
bool RecordDataOps::Write(QTextStream &out, TableEntity *te, RecordEntity *re)
{
    try
        {
            // Get field number and save the value of each field  one by one.
            int nFieldNum = te->GetFieldNum();
            for(int i = 0; i < nFieldNum; i++)
            {
                // Get field information.
                FieldEntity* pField = te->GetFieldAt(i);

                // Get the value of the field, the data type is QString. Before you save the need for type conversion
                QString strFieldName = pField->GetName();
                QString strVal = re->Get(strFieldName);

                // Get to the data type of the field.
                out << strVal << " ";

            }// end for
            out<<"\r\n";
            return true;
        }
        catch (QException e)
        {
            throw new AppException(QString::fromLocal8Bit ("Failed to save record!"));
        }

        return false;

}
/**************************************************
[FunctionName]	Read
[Function]	Read a record from the file
[Argument]	CFile &file: Open file of data record
            CTableEntity &te: Table structure information
            CRecordEntity &re: Record information entity
[ReturnedValue]	bool: True if the operation is successful;otherwise false.
**************************************************/
bool RecordDataOps::Read(QTextStream &in, TableEntity &te, RecordEntity &re)
{
    try
        {
            //QTextStream in(&file);
            // Get field number and read the value of each field  one by one.
            int nFieldNum = te.GetFieldNum();
            QString string = in.readLine();
            QStringList strlist=string.split(" ");
            for(int i = 0; i < nFieldNum; i++)
            {
                // Get field information.
                QString strVal = strlist[i];
                FieldEntity* pField = te.GetFieldAt(i);
                QString strFieldName = pField->GetName();// Field name

                switch (pField->GetDataType())
                {
                case FieldEntity::DT_INTEGER: // Integer
                    {
                        int nVal;
                        nVal = strVal.toInt(&ok,10);
                        re.Put(strFieldName, nVal);
                        break;
                    }
                case FieldEntity::DT_BOOL : // Boolean
                    {
                        bool bVal;
                        bVal = strVal.toInt(&ok,10);
                        re.Put(strFieldName, bVal);
                        break;
                    }
                case FieldEntity::DT_DOUBLE : // Floating-point number
                    {
                        double dbVal;
                        dbVal = strVal.toDouble();
                        re.Put(strFieldName, dbVal);
                        break;
                    }
                case FieldEntity::DT_DATETIME : // Time type
                    {
                        QDateTime st;
                        st = QDateTime::fromString(strVal, "yyyy-MM-dd hh:mm:ss");
                        re.Put(strFieldName, st);
                        break;
                    }
                case FieldEntity::DT_VARCHAR : // String type
                    {
                        re.Put(strFieldName, strVal);
                        // Release cache
                        break;
                    }
                default : // Other data types
                    {
                        throw new AppException(QString::fromLocal8Bit ("Field data type is unusual, read record failed!"));
                    }
                }// end switch
            }// end for
            return true;
        }
        catch (QException e)
        {
            throw new AppException(QString::fromLocal8Bit ("Failed to read record!"));
        }

        return false;
}

/**
 * @brief RecordDataOps::ModifyAndDelete
 * @param tbfile .tb文件
 * @param te
 * @param arrRe
 * @return
 */
bool RecordDataOps::ModifyAndDelete(const QString tbfile,TableEntity &te, RECORDARR &arrRe)
{
    try
        {
            QFile file(te.GetTrdPath());   //打开文件
            file.open(QIODevice::WriteOnly|QIODevice::Truncate);
//            if (file.open(QIODevice::WriteOnly|QIODevice::Truncate) == FALSE)
//            {
//                return false;
//            }
            QTextStream out(&file);
            bool record_num=false;  //记录记录数目是否发生变化

            for(int i=0;i<te.GetFieldNum();i++)
            {
                FieldEntity *fe=te.GetFieldAt(i);
                if(fe->GetParam()!=0) //判断是否为索引
                {
                    QFileInfo fileinfo(te.GetTdfPath());
                    QString ixFilePath=QString("%1/%2.ix").arg(fileinfo.path(),fe->GetName());
                    QFile ixFile(ixFilePath);
                    ixFile.open(QIODevice::Truncate|QIODevice::WriteOnly);
                    ixFile.close();
                }
            }

            for(int i=0;i<arrRe.size();i++)
            {
                RecordEntity* re=arrRe.value(i);
                if(re!=NULL)
                {
                    qint64 pos=out.device()->pos();
                    Write(out,&te,re);
                    record_num=true;

                    /**
                      * 维护index
                      */
                    for(int j=0;j<te.GetFieldNum();j++)
                    {
                        FieldEntity *fe=te.GetFieldAt(j);
                        if(fe->GetParam()!=0) //判断是否为索引
                        {
                            QFileInfo fileinfo(te.GetTdfPath());
                            QString ixFilePath=QString("%1/%2.ix").arg(fileinfo.path(),fe->GetName());
                            QFile ixFile(ixFilePath);
                            QDataStream ixout(&ixFile);
                            ixFile.open(QIODevice::Append|QIODevice::WriteOnly);
                            switch(fe->GetDataType())
                            {
                            case 1:  //int
                            {
                                int data=re->Get(fe->GetName()).toInt(&ok,10);
                                ixout<<data;
                                ixout<<pos;
                                break;
                            }
                            case 3:  //double
                            {
                                double data=re->Get(fe->GetName()).toDouble(&ok);
                                ixout<<data;
                                ixout<<pos;
                                break;
                            }
                            case 4:  //varchar
                            {
                                char* data=new char[256];
                                memcpy(data,re->Get(fe->GetName()).toLatin1().data(),256);
                                ixout<<data;
                                ixout<<pos;
                                delete data;
                                break;
                            }
                            default:
                                break;
                            }
                            ixFile.close();
                        }
                    }
                }
            }

            file.close();
        }
        catch (QString Exception)
        {
            throw new AppException(QString::fromLocal8Bit ("Failed to save record!"));
        }

        return false;
}

bool RecordDataOps::SelectOne(FieldEntity filed,QString value,TableEntity &te, RecordEntity &re)
{
    QFileInfo fileinfo(te.GetTdfPath());
    QString ixFilePath=QString("%1/%2.ix").arg(fileinfo.path(),filed.GetName());
    QFile ixFile(ixFilePath);
    ixFile.open(QIODevice::ReadOnly);
    QDataStream in(&ixFile);
    qint64 pos;
    bool isExist=false;

    switch(filed.GetDataType())
    {
    case 1:
    {
        int compareValue=value.toInt(&ok,10);
        int acceptValue;
        while(!in.atEnd())
        {
            in>>acceptValue;
            in>>pos;
            if(acceptValue==compareValue)
            {
                isExist=true;
                break;
            }
        }
        break;
    }
    case 3:
    {
        double compareValue=value.toDouble(&ok);
        double acceptValue;
        while(!in.atEnd())
        {
            in>>acceptValue;
            in>>pos;
            if(acceptValue==compareValue)
            {
                isExist=true;
                break;
            }
        }
        break;
    }
    case 4:
    {
        char *acceptValue=new char[256];
        while(!in.atEnd())
        {
            in>>acceptValue;
            in>>pos;
            if(QString::compare(QString(acceptValue),value)==0)
            {
                isExist=true;
                break;
            }
        }
        delete acceptValue;
        break;
    }
    default:
        break;
    }
    ixFile.close();

    if(!isExist)
        return false;

    QFile file(te.GetTrdPath());
    file.open(QIODevice::ReadOnly);
    QTextStream read(&file);
    file.seek(pos);
    Read(read,te,re);
    file.close();
    return true;
}

bool RecordDataOps::Select(SEARCHARRAY search_arr,TableEntity &te, RECORDARR &reArr)
{
    QFile file(te.GetTrdPath());
    QTextStream in(&file);
    int nCount=0;
    // Open file
    if (file.open(QIODevice ::ReadOnly) == FALSE)
    {
        return 0;
    }

    while (!in.atEnd())
    {
        // Get the value to write
        RecordEntity* pRecordEntity = new RecordEntity();
        if (Read(in, te, *pRecordEntity) == true)  //将所有记录读出来，插入到QHash中
        {
            if(Compare(search_arr,te,*pRecordEntity))
            {
                reArr.insert(nCount,pRecordEntity);
                nCount++;
            }

        }
        else
        {
            delete pRecordEntity;
            break;// Exit the while loop
        }
    }
    // Close file
    file.close();
}

bool RecordDataOps::Compare(SEARCHARRAY search_arr,TableEntity &te,RecordEntity &re)
{
    int right=0;
    QHashIterator<int,QString> it(search_arr);
    while(it.hasNext())
    {
         it.next();
         int key=it.key();
         QString value=it.value();
         if(QString::compare(value,re.Get(te.GetFieldAt(key)->GetName()))==0)
         {
             right++;
         }
    }

    if(right==search_arr.size())
        return true;
    else
        return false;
}
