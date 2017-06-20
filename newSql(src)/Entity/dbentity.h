#ifndef DBENTITY_H
#define DBENTITY_H
#include "./Global/datastructure.h"
#include "./Global/ref.h"
#include"./tableentity.h"
class DBEntity
{
public:
    // Initialize the data members
    DBEntity(void);
    // Use DatabaseBlock structure to initialize the data members
    DBEntity(DatabaseBlock &db);
    // Initialize the database name
    DBEntity(const QString strName);
    // Destructor
    ~DBEntity(void);

public:
    // Class and block conversion function
    DatabaseBlock GetBlock(void);
    void SetBlock(DatabaseBlock db);

    // Set function
    void SetName(QString strName);
    void SetType(bool bType);
    void SetFilepath(QString strFilepath);
    void SetCtTime(QDateTime tTime);
    QHash<int,TableEntity*>& getTbArr();

    // Get function
    QString GetName(void);
    bool GetType(void);
    QString GetFilepath(void);
    QDateTime GetCtTime(void);

private:
    QString m_strName;		// Database name
    bool m_bType;			// Database type
    QString m_strFilepath;	// The database data file path
    QDateTime m_tCtTime;	// Creation time
    TABLEARR m_arrTable;
};
typedef QHash<int, DBEntity*> DBARR;
#endif // DBENTITY_H
