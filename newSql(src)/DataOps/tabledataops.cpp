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

            out << tb.name;
            out<<tb.record_num;
            out<<tb.field_num;
            out<<tb.tdf;
            out<<tb.trd;
            out<<tb.tic;
            out<<c_Crtime;
            out<<c_Mtime;

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
            delete c_Crtime;
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
            QHash<int,QString>::const_iterator i;
            for(i = fe->getConstrArr().constBegin();i != fe->getConstrArr().constEnd();++i){
                strcpy(c_Value,i.value().toLatin1().data());
                out <<fb.name <<i.key()<<c_Value;  //格式：字段名+约束类型+默认值（没有的话写入"null"）
            }
            // Close file
            delete c_Value;
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
                in>>p;
                strcpy(tb.tic,p);
                in>>p; tb.crtime=QDateTime::fromString(QString(p),"yyyy-MM-dd hh:mm:ss");
                in>>p; tb.mtime=QDateTime::fromString(QString(p),"yyyy-MM-dd hh:mm:ss");
                pTable->SetBlock(tb);
                arr->insert(nCount,pTable);
                nCount++;
            }
            // Close file
            delete p;
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
            delete p;
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
                        pField->getConstrArr().insert(type,Value);
                    }
                }

                // Close file
                delete p;
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
bool TableDataOps::AlterTable(const QString strFilePath,TABLEARR& tba)
{
    try
        {
            char *p,*c_Crtime,*c_Mtime;
            QFile file(strFilePath);
            QDataStream out(&file);
            // Open file
            if (file.open(QIODevice ::Truncate|QIODevice::WriteOnly) == FALSE)
            {
                return false;
            }

            //file.SeekToBegin();
            file.seek(0);
            int i;
            p = new char[256];
            c_Crtime = new char[256];
            c_Mtime = new char[256];
            for(i = 0;i < tba.size();i++){
                if(tba.value(i) != NULL){
                    // Query table information according to the table name, then alter the it
                    TableBlock tb = tba.value(i)->GetBlock();
                    strcpy(c_Crtime,tb.crtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
                    strcpy(c_Mtime,tb.mtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
                    out << tb.name<<tb.record_num<<tb.field_num<<tb.tdf<<tb.trd<<tb.tic<<c_Crtime<<c_Mtime;
                }
            }

            // Close file
            delete p;
            delete c_Crtime;
            delete c_Mtime;
            file.close();
            return true;
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
/**
 * @brief TableDataOps::AlterTableName
 * @param strFilePath .tb文件
 * @param DirFile 表格文件夹
 * @param te
 * @return
 */
bool TableDataOps::AlterTableName(const QString strFilePath, const QString DirFile,TableEntity * te,TABLEARR& tba)
{
    try
        {
        AlterTable(strFilePath,tba);

        QDir dir(DirFile);
        dir.setFilter(QDir::Dirs|QDir::Files); //处理目录和文件其他的过滤掉
        //过滤文件
        QStringList filter;
        filter<<"*.tdf"<<"*.tic"<<"*.trd";
        dir.setNameFilters(filter);
        //获取文件夹下文件信息列表
        QFileInfoList list = dir.entryInfoList();
        for(int i=0;i<list.size();i++)
        {
            QFileInfo fileinfo=list.at(i);
            QString strFile=fileinfo.filePath();  //返回文件路径，包含文件名
            QString suffix=fileinfo.suffix();  //返回后缀名称
            QString newFile=QString("%1/%2.%3").arg(fileinfo.path(),te->GetName(),suffix);
            QFile f(strFile);
            f.rename(strFile,newFile);
        }
        QFileInfo fileinfo(te->GetTdfPath());
        FileLogic fl;
        dir.rename(fl.GetAbsolutePath(DirFile),fl.GetAbsolutePath(fileinfo.path()));
        return true;
        }
        catch (QException e)
        {
            throw new AppException(QString::fromLocal8Bit("Failed to alert table!"));
        }
        return false;
}

bool TableDataOps::AlterField(TableEntity *te,FieldEntity oldfield,FieldEntity newfield)
{
    //修改tdf文件
    {
        QFile file(te->GetTdfPath());
        file.open(QIODevice::Truncate|QIODevice::WriteOnly);
        QDataStream out(&file);
        char* c_Crtime = new char[256];;
        FIELDARRAY arrfield=te->m_arrFields;
        for(int i=0;i<arrfield.size();i++)
        {
            FieldEntity* field=arrfield.value(i);
            FieldBlock fb = field->GetBlock();
            strcpy(c_Crtime,fb.mtime.toString("yyyy-MM-dd hh:mm:ss").toLatin1().data());
            out <<fb.name<<fb.type<<fb.param<<c_Crtime<<fb.integrities;
        }
        delete c_Crtime;
        file.close();
    }

    //维护索引
    {
        if((oldfield.GetParam()==0)&&(newfield.GetParam()==1))  //添加索引文件并维护
        {
            QFileInfo fileinfo(te->GetTdfPath());
            QString ixFilePath=QString("%1/%2.ix").arg(fileinfo.path(),newfield.GetName());
            QFile ixFile(ixFilePath);
            ixFile.open(QIODevice::WriteOnly);
            QDataStream ixout(&ixFile);

            QFile trdFile(te->GetTrdPath());
            trdFile.open(QIODevice::ReadOnly);
            QTextStream trdin(&trdFile);

            qint64  pos=0;
            bool ok;
            while(!trdin.atEnd())
            {
                RecordDataOps rdo;
                RecordEntity re;

                pos=trdFile.pos();
                rdo.Read(trdin,*te,re);

                switch(newfield.GetDataType())
                {
                case 1:  //int
                {
                    int data=re.Get(newfield.GetName()).toInt(&ok,10);
                    ixout<<data;
                    ixout<<pos;
                    break;
                }
                case 3:  //double
                {
                    double data=re.Get(newfield.GetName()).toDouble(&ok);
                    ixout<<data;
                    ixout<<pos;
                    break;
                }
                case 4:  //varchar
                {
                    char* data=new char[256];
                    memcpy(data,re.Get(newfield.GetName()).toLatin1().data(),256);
                    ixout<<data;
                    ixout<<pos;
                    delete data;
                    break;
                }
                default:
                    break;
                }
            }
            ixFile.close();
            trdFile.close();
        }else if((oldfield.GetParam()==1)&&(newfield.GetParam()==0))  //删除索引文件
        {
            QFileInfo fileinfo(te->GetTdfPath());
            QString ixFilePath=QString("%1/%2.ix").arg(fileinfo.path(),oldfield.GetName());
            QFile ixFile(ixFilePath);
            ixFile.remove();
        }

        //修改索引文件名
        QFileInfo fileinfo(te->GetTdfPath());
        QString oldIXFilePath=QString("%1/%2.ix").arg(fileinfo.path(),oldfield.GetName());
        QString newIXFilePath=QString("%1/%2.ix").arg(fileinfo.path(),newfield.GetName());
        QFile ixFile(oldIXFilePath);
        ixFile.rename(oldIXFilePath,newIXFilePath);
    }

    return true;
}

bool TableDataOps::delField(QString fieldName,int param,const QString tbfile,TableEntity *te,RECORDARR &arrRe)
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
        tdfFile.close();


    //删除索引文件
    {
        if(param == 1){
            QFileInfo fileinfo(te->GetTdfPath());
            QString ixFilePath=QString("%1/%2.ix").arg(fileinfo.path(),fieldName);
            QFile ixFile(ixFilePath);
            ixFile.remove();
        }

    }

    //修改trd记录文件以及维护索引文件
    {
        //重置索引文件
        bool ok;//StringToInt
        for(int i=0;i<te->GetFieldNum();i++)
        {
            FieldEntity *fe=arrfield.value(i);
            if(fe!=NULL) //判断是否为索引
            {
                if(fe->GetParam()!=0)
                {
                    QFileInfo fileinfo(te->GetTdfPath());
                    QString ixFilePath=QString("%1/%2.ix").arg(fileinfo.path(),fe->GetName());
                    QFile ixFile(ixFilePath);
                    ixFile.open(QIODevice::Truncate|QIODevice::WriteOnly);
                    ixFile.close();
                }
            }
        }

        int nFieldNum = te->GetFieldNum();  //字段数量
        qint64 pos;
        QFile trdFile(te->GetTrdPath());
        trdFile.open(QIODevice::Truncate|QIODevice::WriteOnly);
        QTextStream out(&trdFile);

        //重写trd记录文件
        for(int i=0;i<arrRe.size();i++)
        {
            RecordEntity* re=arrRe.value(i);
            pos=out.device()->pos();
            for(int j = 0; j < nFieldNum; j++)
            {
                FieldEntity* pField = arrfield.value(j);

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

            /**
              * 维护index
              */
            for(int j=0;j<te->GetFieldNum();j++)
            {
                FieldEntity *fe=arrfield.value(j);
                if(fe!=NULL) //判断是否为索引
                {
                    if(fe->GetParam()!=0)
                    {
                        QFileInfo fileinfo(te->GetTdfPath());
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
        // Close file
        trdFile.close();
    }

    //修改tb记录文件
    {
        QFile tbFile(tbfile);
        tbFile.open(QIODevice::ReadWrite);
        QDataStream inout(&tbFile);
        char* p=new char[256];
        int numAccept;
        while(!inout.atEnd())
        {
            inout>>p;
            inout>>numAccept;
            if(QString::compare(p,te->GetName())==0)
            {
                inout<<te->GetFieldNum();
                break;
            }
            inout>>numAccept;
            inout>>p;
            inout>>p;
            inout>>p;
            inout>>p;
            inout>>p;
        }
        delete p;
        // Close file
        tbFile.close();
    }

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
            out << tb.name<<tb.record_num<<tb.field_num<<tb.tdf<<tb.trd<<tb.tic<<c_Crtime<<c_Mtime;
        }
    }
    delete c_Crtime; //释放内存
    delete c_Mtime;
    file.close();
    return true;

}

bool TableDataOps::ModifyConstr(const QString strFilePath, TableEntity *te)
{
    try
        {
        QFile file(strFilePath);

        char* c_Value;
        // Open file
        if (file.open(QIODevice ::WriteOnly|QIODevice::Truncate) == FALSE)
        {
            return false;
        }
        QDataStream out(&file);

        c_Value = new char[256];
        for(int j = 0;j < te->m_arrFields.size();j++){
            if(te->m_arrFields.value(j) != NULL){
                FieldBlock fb = te->m_arrFields.value(j)->GetBlock();
                //获取遍历器
                QHash<int,QString>::const_iterator i;
                for(i = te->m_arrFields.value(j)->getConstrArr().constBegin();i != te->m_arrFields.value(j)->getConstrArr().constEnd();++i)
                {
                    strcpy(c_Value,i.value().toLatin1().data());
                    out <<fb.name <<i.key()<<c_Value;  //格式：字段名+约束类型+默认值（没有的话写入"null"）
                }
            }
        }
        // Close file
        delete c_Value;
        file.close();
        return true;
        }
        catch (QString Exception)
        {
            throw new AppException(QString::fromLocal8Bit ("Failed to save record!"));
        }

        return false;
}
