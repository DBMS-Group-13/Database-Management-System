#ifndef TABLELOGIC_H
#define TABLELOGIC_H
#include"./Entity/tableentity.h"
#include"./DataOps/tabledataops.h"
#include"./filelogic.h"
#include"./Util/filehelper.h"
#include"./Util/appexception.h"
class TableLogic
{
public:
    TableLogic();
    // 创建一张表
    bool CreateTable(const QString strDBName, TableEntity &te);
    // 添加一个字段
    bool AddField(const QString strDBName, TableEntity &te, FieldEntity &fe);
    // 查询表的信息
    int GetTables(const QString strDBName, TABLEARR &arrTables);
    //更改表信息
    //bool AlterTable(const QString strFilePath, TableEntity &te);
private:
    TableDataOps t_dataOps;	// 表数据操作对象
    FileLogic fileLogic;	// 文件逻辑层
};

#endif // TABLELOGIC_H
