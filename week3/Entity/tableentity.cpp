#include "Tableentity.h"

/************************************************************************
[FunctionName]	TableEntity
[Function]	Constructor to initialize the data members.
[Argument]	void
************************************************************************/
TableEntity::TableEntity(void)
{
    m_strName = QString::fromLocal8Bit("");			// Table name
    m_nRecordNum = 0;			// Record number
    m_tCrTime = QDateTime::currentDateTime();	// Table creation time
    m_tMTime = m_tCrTime;		// Last modification time
}

/************************************************************************
[FunctionName]	TableEntity
[Function]	Constructor to initialize the data members.
[Argument]	strName: Table name
************************************************************************/
TableEntity::TableEntity(QString strName)
{
    m_strName = strName;		// Table name
    m_nRecordNum = 0;			// Record number
    m_tCrTime = QDateTime::currentDateTime();	// Table creation time
    m_tMTime = m_tCrTime;		// Last modification time
}

/************************************************************************
[FunctionName]	~TableEntity
[Function]	Destructor
[Argument]	void
************************************************************************/
TableEntity::~TableEntity(void)
{
    // Empty field list, free memory.
    // Get the number of elements in the field array.
     QHash<int,FieldEntity *>::const_iterator j;
     for(j = m_arrFields.constBegin();j != m_arrFields.constEnd();++j){
         if(j.value()!=NULL){
             delete j.value();
             (FieldEntity*)(j.value()) = NULL;
         }
     }
     // Empty field array
     m_arrFields.clear();
}

/************************************************************************
[FunctionName]	GetBlock
[Function]	Save table information to a TableBlock structure.
[Argument]	void
[ReturnedValue]	TableBlock: Table information structure
************************************************************************/
TableBlock TableEntity::GetBlock()
{
    TableBlock tb;
    strcpy(tb.name,m_strName.toLatin1().data());
    tb.field_num = m_arrFields.size();
    tb.record_num = m_nRecordNum;
    strcpy(tb.tdf,m_strTdfPath.toLatin1().data());
    strcpy(tb.trd,m_strTrdPath.toLatin1().data());
    tb.crtime = m_tCrTime;
    tb.mtime = m_tMTime;
    return tb;
}

/************************************************************************
[FunctionName]	SetBlock
[Function]	Use the data in a table information structure assignment for the data members.
[Argument]	TableBlock tb: Table information structure
[ReturnedValue]	void
************************************************************************/
void TableEntity::SetBlock(TableBlock tb)
{
    m_strName = tb.name;  //VARCHAR转QString
    m_nRecordNum = tb.record_num;
    m_strTdfPath = tb.tdf;
    m_strTrdPath = tb.trd;
    m_tCrTime = tb.crtime;
    m_tMTime = tb.mtime;
}

//////////////////////////////////////////////////////////////////////////
// Set function
void TableEntity::SetName(QString strName)
{
    m_strName = strName;
}

void TableEntity::SetRecordNum(int nNum)
{
    m_nRecordNum = nNum;
}

void TableEntity::SetTdfPath( const QString strTdfPath )
{
    m_strTdfPath = strTdfPath;
}

void TableEntity::SetTrdPath( const QString strTrdPath )
{
    m_strTrdPath = strTrdPath;
}

void TableEntity::SetCrTime(QDateTime tTime)
{
    m_tCrTime = tTime;
}

void TableEntity::SetMTime(QDateTime tTime)
{
    m_tMTime = tTime;
}

//////////////////////////////////////////////////////////////////////////
// Get function
QString TableEntity::GetName()
{
    return m_strName;
}

int TableEntity::GetRecordNum()
{
    return m_nRecordNum;
}

int TableEntity::GetFieldNum()
{
    return m_arrFields.size();
}

QString TableEntity::GetTdfPath()
{
    return m_strTdfPath;
}

QString TableEntity::GetTrdPath()
{
    return m_strTrdPath;
}

QDateTime TableEntity::GetCrTime()
{
    return m_tCrTime;
}

QDateTime TableEntity::GetMTime()
{
    return m_tMTime;
}

//////////////////////////////////////////////////////////////////////////
// Field operation
/************************************************************************
[FunctionName]	AddField
[Function]	Add field
[Argument]	FieldEntity &fe: Field entity
[ReturnedValue]	FieldEntity*: Pointer to the field
************************************************************************/
FieldEntity* TableEntity::AddField(FieldEntity &fe)
{
    // Add field
    FieldEntity* pField = new FieldEntity(fe);
    int nCount = m_arrFields.size();
    m_arrFields.insert(nCount,pField);

    return pField;
}

/************************************************************************
[FunctionName]	GetFieldAt
[Function]	Get a certain field in store order
[Argument]	int nIndex: field index
[ReturnedValue]	FieldEntity*: Pointer to the field
************************************************************************/
FieldEntity* TableEntity::GetFieldAt(int nIndex)
{
   return (FieldEntity*)m_arrFields.value(nIndex);
}
