#include "Recordentity.h"

// Constructor
RecordEntity::RecordEntity(void)
{
}

// Copy constructor
RecordEntity::RecordEntity(RecordEntity &e)
{
    //QHash<int, FieldEntity*>::const_iterator i = m_arrFields.find(nIndex);
    i = e.m_mapData.constBegin();          //获取集合第一个元素的迭代器
    QString strFieldName, strValue;
    while(i!=e.m_mapData.end())
    {
        //e.m_mapData.GetNextAssoc(pos, strFieldName, strValue);
        strFieldName = i.key();
        strValue = i.value();
        m_mapData.insert(strFieldName, strValue);     //插入集合
        ++i;
    }
}

// Destructor
RecordEntity::~RecordEntity(void)
{
}

// Overload "=" operator
RecordEntity &RecordEntity::operator =(const RecordEntity &e)
{
    QString strFieldName, strValue;
    i = e.m_mapData.constBegin();     //获取集合第一个元素的迭代器
    while(i!=e.m_mapData.end())
    {
        strFieldName = i.key();
        strValue = i.value();
        m_mapData.insert(strFieldName, strValue);  //插入集合
        ++i;
    }

    return *this;
}

// Add record
void RecordEntity::Put(QString strFieldName, QString strValue)
{
    m_mapData.insert(strFieldName, strValue);
}

void RecordEntity::Put(QString strFieldName, int nValue)
{
    QString strValue;
    strValue = QString("%1").arg(nValue);
    m_mapData.insert(strFieldName, strValue);
}
void RecordEntity::Put(QString strFieldName, double dbValue)
{
    QString strValue;
    strValue = QString("%1").arg(dbValue);
    m_mapData.insert(strFieldName, strValue);
}

void RecordEntity::Put(QString strFieldName, QDateTime t)
{
    QString strValue;
    strValue = t.toString("yyyy-MM-dd hh:mm:ss");
    m_mapData.insert(strFieldName, strValue);
}

// Get the value of the field.After removed, needs to be transformed according to the data type of the field.
QString RecordEntity::Get(QString strFieldName)
{
    return m_mapData.value(strFieldName);
}

QHash<QString, QString>& RecordEntity::getReArr(){
    return m_mapData;
}
