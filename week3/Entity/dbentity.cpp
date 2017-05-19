#include "dbentity.h"
DBEntity::DBEntity(void)
{

}


DBEntity::DBEntity(const QString strName)
{
    m_strName=strName;		// Database name
    m_bType=true;			// Database type
    m_strFilepath=QString("./DBMS_ROOT/data/%1").arg(strName); // The database data file path
    m_tCtTime=QDateTime::currentDateTime();	// Creation time
}

DBEntity::DBEntity(DatabaseBlock &db)
{
    m_strName=db.name;		// Database name
    m_bType=db.type;			// Database type
    m_strFilepath=db.filepath;	// The database data file path
    m_tCtTime=db.crtimAe;	// Creation time
}

DBEntity::~DBEntity(void)
{

}

DatabaseBlock DBEntity::GetBlock(void)
{
    DatabaseBlock db;
    //将QString转为char*再通过strcpy拷贝到VARCHAR类型变量中
    strcpy(db.name,m_strName.toLatin1().data());
    //strcpy(db.name,m_strNameCopy);
    db.type=m_bType;
    strcpy(db.filepath,m_strFilepath.toLatin1().data());
    db.crtimAe=m_tCtTime;
    return db;
}

void DBEntity::SetBlock(DatabaseBlock db)
{
    m_strName=db.name;
    m_bType=db.type;
    m_strFilepath=db.filepath;
    m_tCtTime=db.crtimAe;
}

void DBEntity::SetName(QString strName)
{
    m_strName=strName;
}

void DBEntity::SetType(bool bType)
{
    m_bType=bType;
}

void DBEntity::SetFilepath(QString strFilepath)
{
    m_strFilepath=strFilepath;
}

void DBEntity::SetCtTime(QDateTime tTime)
{
    m_tCtTime=tTime;
}

QString DBEntity::GetName()
{
    return m_strName;
}

bool DBEntity::GetType()
{
    return m_bType;
}

QString DBEntity::GetFilepath()
{
    return m_strFilepath;
}

QDateTime DBEntity::GetCtTime()
{
    return m_tCtTime;
}
QHash<int,TableEntity*>& DBEntity::getTbArr(){
    return m_arrTable;
}
