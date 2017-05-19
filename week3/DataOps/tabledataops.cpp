#include "tabledataops.h"
#include "./Logic/filelogic.h"
#include "./Entity/recordentity.h"

TableDataOps::TableDataOps()
{

}

/**************************************************
[FunctionName]	Create
[Function]	Create table and save table information
[Argument]	const CString strFilePath: Path of the table description file
        CTableEntity &te: Table information entity
[ReturnedValue]	bool: True if the operation is successful,otherwise false
**************************************************/
bool TableDataOps::Create(const QString strFilePath, TableEntity *te)
{
    try
        {
            char* c_Crtime;
            char* c_Mtime;
            QFile file(strFilePath);

            // Open file
            if (file.open(QIODevice ::WriteOnly|QIODevice::Append) == FALSE)
            {
                return false;
            }
            QDataStream out(&file);
            // Write in the database table information to the file

            TableBlock tb = te->GetBlock();
            c_Crtime = new char[256];
            c_Mtime = new char[256];
            strcpy(c_Crtime,tb.crtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());;
            strcpy(c_Mtime,tb.mtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());

            out << tb.name<<tb.record_num<<tb.field_num<<tb.tdf<<tb.trd<<c_Crtime<<c_Mtime;

            // Close file
            delete c_Crtime;
            delete c_Mtime;
            file.close();
            return true;
        }
        catch (QException e)
        {
            throw new AppException(QString::fromLocal8Bit("Failed to add table information!"));
        }
        return false;
}


/**************************************************
[FunctionName]	AddField
[Function]	Add table field
[Argument]	const CString strFilePath: Path of the table definition file
        CFieldEntity &te: Field information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool TableDataOps::AddField(const QString strFilePath, FieldEntity *fe)
{
    try
        {
            QFile file(strFilePath);

            char* c_Crtime;
            // Open file
            if (file.open(QIODevice ::WriteOnly|QIODevice::Append) == FALSE)
            {
                return false;
            }
            QDataStream out(&file);

            // Add field informaiton
            c_Crtime = new char[256];
            FieldBlock fb = fe->GetBlock();
            strcpy(c_Crtime,fb.mtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());

            out <<fb.name<<fb.type<<fb.param<<c_Crtime<<fb.integrities;

            // Close file
            file.close();
            return true;
        }
        catch (QException e)
        {
            //delete
            throw new AppException(QString::fromLocal8Bit("Failed to add field!"));
        }
        return false;
}

/**************************************************
[FunctionName]	AddConstr
[Function]	Add constraint condition
[Argument]	const CString strFilePath: Path of the table definition file
        CFieldEntity &te: Field information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool TableDataOps::AddConstr(const QString strFilePath, FieldEntity *fe)
{
    try
        {
            QFile file(strFilePath);

            char* c_Value;
            // Open file
            if (file.open(QIODevice ::WriteOnly|QIODevice::Append) == FALSE)
            {
                return false;
            }
            QDataStream out(&file);

            c_Value = new char[256];
            FieldBlock fb = fe->GetBlock();

            //获取遍历器
            QHashIterator<int, QString> i(fe->m_arrconstr);
               while (i.hasNext()) {
                   strcpy(c_Value,i.value().toLatin1().data());
                   out <<fb.name <<i.key()<<i.value();  //格式：字段名+约束类型+默认值（没有的话写入"null"）
               }

            // Close file
            file.close();
            return true;
        }
        catch (QException e)
        {
            //delete
            throw new AppException(QString::fromLocal8Bit("Failed to add field!"));
        }
        return false;
}
/**************************************************
[FunctionName]	GetTables
[Function]	Read the table information from the table description file. With this information,
            you can find the table structure definition file.
[Argument]	const QString strFilePath: Path of the table description file
        TABLEARR &arrTables: Table information array, This is an output parameter, used to save the queried table information.
[ReturnedValue]	int: The number of the queried table.
**************************************************/
int TableDataOps::GetTables(const QString strFilePath, TABLEARR *arr )
{
    try
        {
            char* p;
            QFile file(strFilePath);

            // Open file
            if (file.open(QIODevice ::ReadOnly) == FALSE)
            {
                return false;
            }
            QDataStream in(&file);

            TableBlock tb;
            int nCount = 0;
            p=new char[256];
            // Read table information
            while(!in.atEnd())
            {
                TableEntity* pTable = new TableEntity();
                in>>p;
                strcpy(tb.name,p);
                in>>tb.record_num;
                in>>tb.field_num;
                in>>p;
                strcpy(tb.tdf,p);
                in>>p;
                strcpy(tb.trd,p);
                in>>p; tb.crtime=QDateTime::fromString(QString(p),"yyyy-MM-dd hh:mm:ss");
                in>>p; tb.mtime=QDateTime::fromString(QString(p),"yyyy-MM-dd hh:mm:ss");
                pTable->SetBlock(tb);
                arr->insert(nCount,pTable);
                nCount++;
            }
            // Close file
            file.close();
            return nCount;
        }
    catch (QException e)
    {
        throw new AppException(QString::fromLocal8Bit("Failed to add field!"));
    }
    return false;
}


/**************************************************
[FunctionName]	GetFields
[Function]	Read fields information from the table definition file.
[Argument]	const CString strFilePath: Path of the table definition file
        CTableEntity &te: Table information entities.this is an output parameter.
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool TableDataOps::GetFields(const QString strFilePath, TableEntity *te)
{
    try
        {
            QFile file(strFilePath);
            QDataStream in(&file);
            char* p;
            // Open file
            if (file.open(QIODevice ::ReadOnly) == FALSE)
            {
                return false;
            }

            // Read field information
            FieldBlock fb;
            p = new char[256];
            // Read table information
            while(!in.atEnd())
            {
                FieldEntity fe;
                in>>p;
                strcpy(fb.name,p);
                in>>fb.type;
                in>>fb.param;
                in>>p;
                fb.mtime=QDateTime::fromString(QString(p),"yyyy-MM-dd hh:mm:ss");
                in>>fb.integrities;
                fe.SetBlock(fb);
                te->AddField(fe);
            }

            // Close file
            file.close();
            return true;
        }
        catch (QException e)
        {
            throw new AppException(QString::fromLocal8Bit("Failed to read field information!"));
        }
        return false;
}

/**************************************************
[FunctionName]	GetConstr
[Function]	Read constraint condition information from the table definition file.
[Argument]	const CString strFilePath: Path of the table definition file
        CTableEntity &te: Table information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false
**************************************************/
bool TableDataOps::GetConstr(const QString strFilePath, TableEntity *te)
{
    try
        {
            QFile file(strFilePath);
            QDataStream in(&file);
            char* p;

            int nFieldNum = te->GetFieldNum();
            for(int i = 0; i < nFieldNum; i++)
            {
                // Open file
                if (file.open(QIODevice ::ReadOnly) == FALSE)
                {
                    return false;
                }
                // Get field information.
                FieldEntity* pField = te->GetFieldAt(i);

                // Get the value of the field, the data type is CString. Before you save the need for type conversion
                QString strFieldName = pField->GetName();

                p = new char[256];
                QString str,Value;
                int type;
                // Read table information
                while(!in.atEnd())
                {
                    in>>p;
                    str = p;
                    in>> type;
                    in>>p;
                    Value = p;
                    if (QString::compare(strFieldName,str,Qt::CaseInsensitive) == 0)
                    {
                        pField->m_arrconstr.insert(type,Value);
                    }
                }

                // Close file
                file.close();
            }

            return true;
        }
        catch (QException e)
        {
            throw e;
        }
        return false;
}


/**************************************************
[FunctionName]	AlterTable
[Function]	Alter the table information
[Argument]	const CString strFilePath: Path of the table definition file
        CTableEntity &te: Table information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false
**************************************************/
bool TableDataOps::AlterTable(const QString strFilePath, TableEntity *te)
{
    try
        {
            char *p,*c_Crtime,*c_Mtime;
            QFile file(strFilePath);
            QDataStream inout(&file);
            // Open file
            if (file.open(QIODevice ::ReadWrite) == FALSE)
            {
                return false;
            }

            //file.SeekToBegin();
            file.seek(0);

            // Query table information according to the table name, then alter the it
            bool flag = false;
            p = new char[256];
            c_Crtime = new char[256];
            c_Mtime = new char[256];
            int tmp;
            int pos = 0;
            while(!inout.atEnd())
            {
                //将分割出来的字符串数组转成结构体中的数据类型
                inout>>p;
                QString str = p;
                inout>>tmp;
                inout>>tmp;
                inout>>p;
                inout>>p;
                inout>>p;
                inout>>p;
                 //Compare the table name
                if (QString::compare(te->GetName(),str,Qt::CaseInsensitive) == 0)
                {
                    inout.resetStatus();
                    file.seek(pos);
                    TableBlock tb = te->GetBlock();
                    strcpy(c_Crtime,tb.crtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
                    strcpy(c_Mtime,tb.mtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
                    inout << tb.name<<tb.record_num<<tb.field_num<<tb.tdf<<tb.trd<<c_Crtime<<c_Mtime;
                    flag = true;
                    break;
                }
                pos = file.pos();
            }

            // Close file
            file.close();
            return flag;
        }
        catch (QException e)
        {
            throw new AppException(QString::fromLocal8Bit("Failed to alert table!"));
        }
        return false;
}

/**************************************************
[FunctionName]	AlterTableName
[Function]	Alter the table name
[Argument]	const CString strFilePath: Path of the table definition file
        CTableEntity &te: Table information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false
**************************************************/
bool TableDataOps::AlterTableName(const QString strFilePath, const QString TableName, TableEntity *te)
{
    try
        {
            char *p,*c_Crtime,*c_Mtime;
            QFile file(strFilePath);
            QDataStream inout(&file);
            // Open file
            if (file.open(QIODevice ::ReadWrite) == FALSE)
            {
                return false;
            }

            //file.SeekToBegin();
            file.seek(0);

            // Query table information according to the table name, then alter the it
            bool flag = false;
            p = new char[256];
            c_Crtime = new char[256];
            c_Mtime = new char[256];
            int tmp;
            int pos = 0;
            while(!inout.atEnd())
            {
                //将分割出来的字符串数组转成结构体中的数据类型
                inout>>p;
                QString str = p;
                inout>>tmp;
                inout>>tmp;
                inout>>p;
                inout>>p;
                inout>>p;
                inout>>p;
                 //Compare the table name
                if (QString::compare(TableName,str,Qt::CaseInsensitive) == 0)
                {
                    inout.resetStatus();
                    file.seek(pos);
                    TableBlock tb = te->GetBlock();
                    strcpy(c_Crtime,tb.crtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
                    strcpy(c_Mtime,tb.mtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
                    inout << tb.name<<tb.record_num<<tb.field_num<<tb.tdf<<tb.trd<<c_Crtime<<c_Mtime;
                    flag = true;
                    break;
                }
                pos = file.pos();
            }

            // Close file
            file.close();
            return flag;
        }
        catch (QException e)
        {
            throw new AppException(QString::fromLocal8Bit("Failed to alert table!"));
        }
        return false;
}

bool TableDataOps::delField(TableEntity *te,RECORDARR &arrRe)
{
    //删除tdf文件中字段
    QFile tdfFile(te->GetTdfPath());
    tdfFile.open(QIODevice::Truncate|QIODevice::WriteOnly);
    QDataStream tdf_out(&tdfFile);
    char* c_Crtime;
    FIELDARRAY arrfield=te->m_arrFields;
    for(int i=0;i<arrfield.size();i++)
    {
        FieldEntity* field=arrfield.value(i);
        if(field!=NULL)
        {
            c_Crtime = new char[256];
            FieldBlock fb = field->GetBlock();
            strcpy(c_Crtime,fb.mtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
            tdf_out <<fb.name<<fb.type<<fb.param<<c_Crtime<<fb.integrities;
        }
    }
    delete c_Crtime;
    tdfFile.flush();
    tdfFile.close();

    //修改trd记录文件
    QFile trdFile(te->GetTrdPath());
    trdFile.open(QIODevice::Truncate|QIODevice::WriteOnly);
    QTextStream out(&trdFile);

    int nFieldNum = te->GetFieldNum();  //字段数量

    for(int i=0;i<nFieldNum;i++)
    {
        RecordEntity* re=arrRe.value(i);
        for(int i = 0; i < nFieldNum; i++)
        {
            FieldEntity* pField = te->GetFieldAt(i);

            if(pField!=NULL)
            {
                // Get the value of the field, the data type is QString. Before you save the need for type conversion
                QString strFieldName = pField->GetName();
                QString strVal = re->Get(strFieldName);

                // Get to the data type of the field.
                out << strVal << " ";
            }

        }
        out<<"\r\n";
    }

    // Close file
    trdFile.flush();
    trdFile.close();
    return true;

}

/**
 * @brief TableDataOps::delTable
 * @param arrtab
 * @param tbFilePath .tb文件夹
 * @param DirPath 表格文件夹
 * @return
 */
bool TableDataOps::delTable(TABLEARR &arrtab,const QString tbFilePath,const QString DirPath)
{
    /*
     * 清空文件夹
     */
    FileLogic fl;
    fl.DeleteDirectory(fl.GetAbsolutePath(DirPath));

    /*
     *  .tb文件夹中删除表信息
     */
    QFile file(tbFilePath);
    QDataStream out(&file);
    file.open(QIODevice::Truncate|QIODevice::WriteOnly);


    char *c_Crtime=new char[256];
    char *c_Mtime=new char[256];
    //遍历TABLEARR
    for(int i=0;i<arrtab.size();i++)
    {
        TableEntity* te=arrtab.value(i);
        if(te!=NULL)
        {
            TableBlock tb = te->GetBlock();
            strcpy(c_Crtime,tb.crtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
            strcpy(c_Mtime,tb.mtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
            out << tb.name<<tb.record_num<<tb.field_num<<tb.tdf<<tb.trd<<c_Crtime<<c_Mtime;
        }
    }
    delete c_Crtime; //释放内存
    delete c_Mtime;
    file.close();
    return true;

}

