#ifndef DBLOGIC_H
#define DBLOGIC_H
#include"./DataOps/dbdataops.h"
#include"./DataOps/tabledataops.h"
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
    // 修改数据库名称
    bool RenameDatabase(QString newDbName,DBEntity * db,DBARR& m_arrDB);
    // 删除指定数据库
    bool DeleteDatabase(QString dbName,DBARR &arrdb);

private:
    DBDataOps DB_Ops;		// The database data operation object
    TableDataOps TB_Ops;
    FileLogic fileLogic;	// The logical object of the database file
};

#endif // DBLOGIC_H
