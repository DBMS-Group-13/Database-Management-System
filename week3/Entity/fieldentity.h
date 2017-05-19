#ifndef FIELDENTITY_H
#define FIELDENTITY_H
#include "./Global/ref.h"
#include"./Global/datastructure.h"
#include<cstring>
typedef QHash<int, QString> CONSTRARRAY;

class FieldEntity
{
public:
    // Field type definitions
    enum DataType
    {
        DT_NONE = 0,
        DT_INTEGER = 1,// Integer: 4byte  corresponding: int
        DT_BOOL = 2,// Boolean: 1byte, corresponding：bool
        DT_DOUBLE = 3,// Floating-point number: 2byte,  corresponding: double
        DT_VARCHAR = 4,// String: 256byte, corresponding: char[256]
        DT_DATETIME = 5// Data time: 16byte, corresponding: SYSTEMTIME type
    };

public:
    // Constructor
    FieldEntity(QString strName, int nType = DT_INTEGER, int nParam = NULL, int nIntegrities = 0);
    FieldEntity(FieldEntity& fe);
    FieldEntity(void);
    ~FieldEntity(void);

    // Get the name of the data type
    QString GetTypeName(int nType);

    // Class and block conversion function
    FieldBlock GetBlock();
    void SetBlock(FieldBlock fb);

    // Set function
    void SetName(QString strName);
    void SetDataType(int nType);
    void SetParam(int nParam);
    void SetMTime(QDateTime t);

    // Get function
    QString GetName();
    int GetDataType();
    int GetParam();
    QDateTime GetMTime();

    //add function
    bool FieldEntity::AddConstr(int type, QString value);

private:
    QString m_strName;  // Field name
    int m_nType; // Field type
    int m_nParam;  // Field type parameter
    QDateTime m_tMTime; // Last modification time
    int m_nIntegrities; // Type of integrity constraints
    QByteArray ba;

public:
    CONSTRARRAY m_arrconstr;
};
typedef QHash<int, FieldEntity*> FIELDARRAY;
#endif // FIELDENTITY_H
