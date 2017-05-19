#ifndef RECORDLOGIC_H
#define RECORDLOGIC_H
#include"./Entity/tableentity.h"
#include"./Entity/recordentity.h"
#include"filelogic.h"
#include"./DataOps/recorddataops.h"
#include"./DataOps/tabledataops.h"
#include"./Util/filehelper.h"
#include"./Util/appexception.h"
class RecordLogic
{
public:
    RecordLogic();
    // 往表中插入数据
    bool Insert(const QString strDBName, TableEntity &te, RecordEntity &re);
    // 从指定表中提取所有记录
    bool SelectAll(TableEntity &te, RECORDARR &data);
private:
    RecordDataOps r_dataOps;	// 记录操作对象
    TableDataOps t_dataOps;	// 表操作对象
    FileLogic fileLogic;	// 文件逻辑层
};

#endif // RECORDLOGIC_H
