#ifndef SERVICE_H
#define SERVICE_H
#include"./Entity/tableentity.h"
#include"./Entity/dbentity.h"
#include"./Entity/recordentity.h"
#include"./Entity/dbentity.h"
class service
{
public: // create from serialization only
    service();
    ~service(void);

DBARR m_arrDB;
public:
    DBEntity* m_dbEntity;	// Database entity object
    QString m_strError;		// Exception information
    TABLEARR m_arrTable;	// Table array
    TableEntity* m_tbEntity;	// Current edit form
    RECORDARR m_arrRecord;	// Record information

// Generated message map functions
protected:
#ifdef SHARED_HANDLERS
    // Helper function that sets search content for a Search Handler
#endif // SHARED_HANDLERS


public:
    QString GetError();					//	Get exception information
    void SetError(QString strError);	//	Set exception information

    void CleanContainer();

    DBEntity* GetDBEntity();			//	Get the database entities
    void SetCurDB(QString strDBName);
    void LoadDatabases(void);
    DBEntity* CreateDatabase(QString dbname);

    TableEntity* CreateTable(QString strDBName,QString strName);		// Create table
    TableEntity* GetCurTable();					// Get current formvoid
    void SetCurTable(QString strTableName);		// Set the current form
    TableEntity* GetTable(int nIndex);				// Get table
    int GetTableNum();								// Get the number of table information
    void LoadTables(DBEntity* db);							// Load tables

    FieldEntity* AddField(QString strDBName,QString strTBName,FieldEntity &field);	// Add field
    void SetEditTable(TableEntity* pTable);		// Set the current form        


    RecordEntity* InsertRecord(QString strDBName,QString strTBName,RecordEntity &record);	// Insert a record
    int GetRecordNum();								// Get the number of records
    RecordEntity* GetRecord(int nIndex);			// Get a record
    void LoadRecord(QString strDBName,QString strTBName);
};

#endif // SERVICE_H
