#ifndef TABLEENTITY_H
#define TABLEENTITY_H
#include"fieldentity.h"
#include"./Global/datastructure.h"
#include "./Global/ref.h"
class TableEntity
{
public:
    // Constructor
    TableEntity(QString strName);
    TableEntity(void);
    // Destructor
    ~TableEntity(void);

    // Class and block conversion function
    TableBlock GetBlock();
    void SetBlock(TableBlock tb);

    // Set function
    void SetName(QString strName);
    void SetRecordNum(int nNum);
    void SetTdfPath(const QString strTdfPath);
    void SetTrdPath(const QString strTrdPath);
    void SetCrTime(QDateTime tTime);
    void SetMTime(QDateTime tTime);

    // Get function
    QString GetName();
    int GetRecordNum();
    int GetFieldNum();
    QString GetTdfPath();
    QString GetTrdPath();
    QDateTime GetCrTime();
    QDateTime GetMTime();

private:
    QByteArray ba;
    // Table basic information
    QString m_strName;		// Table name
    int m_nRecordNum;		// Record number
    QString m_strTdfPath;	// Tath of table definition file
    QString m_strTrdPath;	// Path of record file
    QDateTime m_tCrTime;	// Table creation time
    QDateTime m_tMTime;	// Last modification time

public:
    // Add field
    FieldEntity* AddField(FieldEntity &fe);
    // Get a field
    FieldEntity* GetFieldAt(int nIndex);

public:
    FIELDARRAY m_arrFields;	// Field array
};

#endif // TABLEENTITY_H
typedef QHash<int, TableEntity*> TABLEARR;
