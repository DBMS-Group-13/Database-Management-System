#include "Recorddataops.h"

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

            // Save record
            Write(out, &te, &re);

            // Close file
            file.close();
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

bool RecordDataOps::ModifyAndDelete(TableEntity &te, RECORDARR &arrRe)
{
    try
        {
            QFile file(te.GetTrdPath());   //打开文件
            if (file.open(QIODevice::WriteOnly|QIODevice::Truncate) == FALSE)
            {
                return false;
            }
            QTextStream out(&file);

            for(int i=0;i<arrRe.size();i++)
            {
                RecordEntity* re=arrRe.value(i);
                if(re!=NULL)
                    Write(out,&te,re);
            }

            file.close();
        }
        catch (QString Exception)
        {
            throw new AppException(QString::fromLocal8Bit ("Failed to save record!"));
        }

        return false;
}

