#ifndef DBLOGIC_H
#define DBLOGIC_H
#include"./DataOps/dbdataops.h"
#include"./filelogic.h"
class DBLogic
{
public:
    DBLogic();
public:
    // 创建数据库
    bool CreateDatabase(DBEntity &db);
    // 查询数据库
    bool GetDatabases(DBARR &m_arrDB);

private:
    DBDataOps DB_Ops;		// The database data operation object
    FileLogic fileLogic;	// The logical object of the database file
};

#endif // DBLOGIC_H
