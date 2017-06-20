#ifndef TABLELOGIC_H
#define TABLELOGIC_H
#include"./Entity/tableentity.h"
#include"./DataOps/tabledataops.h"
#include"./filelogic.h"
#include"./Util/filehelper.h"
#include"./Util/appexception.h"
#include"./Entity/fieldentity.h"
class TableLogic
{
public:
    TableLogic();
    // 创建一张表
    bool CreateTable(const QString strDBName, TableEntity &te);
    // 添加一个字段
    bool AddField(const QString strDBName, TableEntity &te, FieldEntity &fe,TABLEARR &tba);
    // 查询表的信息
    int GetTables(const QString strDBName, TABLEARR &arrTables);
    // 删除表
    bool deleteTable(const QString tbName, const QString dbName, TABLEARR &arrTables);
    // 删除字段
    bool deleteField(const QString dbName,const QString fieldName,TableEntity *te,RECORDARR &arrRe);
    // 修改字段
    bool alterField(FieldEntity *oldfe,TableEntity *te,FieldEntity *newfe);
    // 重命名表
    bool alterTableName(QString DBName,QString TBName,TableEntity * tbe,TABLEARR &tba);
private:
    TableDataOps t_dataOps;	// 表数据操作对象
    FileLogic fileLogic;	// 文件逻辑层
};

#endif // TABLELOGIC_H
