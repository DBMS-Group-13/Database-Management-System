#ifndef DBDATAOPS_H
#define DBDATAOPS_H
#include".\Entity\dbentity.h"
#include<QString>

class DBDataOps
{
public:
    DBDataOps();
    // 创建数据库
    bool Create(const QString strFilepath, DBEntity db, bool bAppend = true);
    // 读取数据库信息
    bool GetDatabase(const QString strFilepath,DBARR &arrDB);
};

#endif // DBDATAOPS_H
