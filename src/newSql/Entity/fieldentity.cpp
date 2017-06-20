#include "Fieldentity.h"

// Constructor
FieldEntity::FieldEntity(void)
{
    m_strName = QString::fromLocal8Bit("");			// Field name
    m_nType = DT_NONE;			// Field type
    m_nParam = -1;				// Field parameter
    m_tMTime = QDateTime::currentDateTime();	// Last modification time
    m_nIntegrities = 0;			// Type of integrity constraints
}

// Constructor
FieldEntity::FieldEntity(QString strName, int nType, int nParam, int nIntegrities)
{
    m_strName = strName;
    m_nType = nType;
    m_nParam = nParam;
    m_nIntegrities = nIntegrities;
    m_tMTime = QDateTime::currentDateTime();
}

// Copy constructor
FieldEntity::FieldEntity(FieldEntity& fe)
{
    m_strName = fe.m_strName;
    m_nType = fe.m_nType;
    m_nParam = fe.m_nParam;
    m_tMTime = fe.m_tMTime;
    m_nIntegrities = fe.m_nIntegrities;
}

// Destructor
FieldEntity::~FieldEntity(void)
{
}

/**************************************************
[FunctionName]	GetTypeName
[Function]	Get the name of the data type
[Argument]	int nDataType: Data type
[ReturnedValue]	CString: Type name
**************************************************/
QString FieldEntity::GetTypeName(int nDataType)
{
    QString strName = QString::fromLocal8Bit(""); //该方法等同于C++中的_T()方法
    switch(nDataType)
    {
    case FieldEntity::DT_INTEGER:	// INT type
        {
            strName = QString::fromLocal8Bit("INT");
            break;
        }
    case FieldEntity::DT_BOOL:		// BOOL type
        {
            strName = QString::fromLocal8Bit("BOOL");
            break;
        }
    case FieldEntity::DT_DOUBLE:	// DOUBLE type
        {
            strName = QString::fromLocal8Bit("DOUBLE");
            break;
        }
    case FieldEntity::DT_VARCHAR:	// VRACHAR type
        {
            strName = QString::fromLocal8Bit("VARCHAR");
            break;
        }
    case FieldEntity::DT_DATETIME:	// DATETIME type
        {
            strName = QString::fromLocal8Bit("DATATIME");
            break;
        }
    default:
        break;
    }
    return strName;
}

//////////////////////////////////////////////////////////////////////////
// Class and block conversion function
void FieldEntity::SetBlock(FieldBlock fb)
{
    m_strName = fb.name;   //将VARCHAR转为QString类型
    m_tMTime = fb.mtime;
    m_nType = fb.type;
    m_nParam = fb.param;
    m_nIntegrities = fb.integrities;
}

FieldBlock FieldEntity::GetBlock()
{
    FieldBlock fb;

    //该方法将QString转为VARCHAR
    strcpy(fb.name,m_strName.toLatin1().data());
    fb.mtime = m_tMTime;
    fb.type = m_nType;
    fb.param = m_nParam;
    fb.integrities = m_nIntegrities;
    return fb;
}

// Set function
void FieldEntity::SetName(QString strName)
{
    m_strName = strName;
}

void FieldEntity::SetDataType(int nType)
{
    m_nType = nType;
}

void FieldEntity::SetParam(int nParam)
{
    m_nParam = nParam;
}

void FieldEntity::SetMTime(QDateTime t)
{
    m_tMTime = t;
}

//////////////////////////////////////////////////////////////////////////
// Get function
QString FieldEntity::GetName()
{
    return m_strName;
}

int FieldEntity::GetDataType()
{
    return m_nType;
}

int FieldEntity::GetParam()
{
    return m_nParam;
}

QDateTime FieldEntity::GetMTime()
{
    return m_tMTime;
}


/************************************************************************
[FunctionName]	AddConstr
[Function]	Add constraint condition
[Argument]	FieldEntity &fe: Field entity
[ReturnedValue]	FieldEntity*: Pointer to the field
************************************************************************/
void FieldEntity::AddConstr(int type, QString value)
{
    // Add constraint condition

    m_arrconstr.insert(type,value);

}

QHash<int, QString>& FieldEntity::getConstrArr(){
    return m_arrconstr;
}

