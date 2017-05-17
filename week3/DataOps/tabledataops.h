#ifndef TABLEDATAOPS_H
#define TABLEDATAOPS_H
#include ".\Entity\TableEntity.h"
#include ".\Entity\FieldEntity.h"
#include ".\Util\Appexception.h"
#include<qexception.h>
#include<QString>
#include <qtextstream.h>
#include <qdatastream.h>
#include <QTextCodec>
#include <qfile.h>
class TableDataOps
{
public:
    TableDataOps();
    // Create table and save table information
    bool Create(const QString strFilePath, TableEntity *te);
    // Add a table field
    bool AddField(const QString strFilePath, FieldEntity *fe);
    // Add constraint condition
    bool AddConstr(const QString strFilePath, FieldEntity *fe);
    // Get table information
    int GetTables(const QString strFilePath, TABLEARR *arr);
    // Get field information
    bool GetFields(const QString strFilePath, TableEntity *te);
    // Alert table
    bool AlterTable(const QString strFilePath, TableEntity *te);
    // Alert table name
    bool AlterTableName(const QString strFilePath,const QString TableName, TableEntity *te);
    // Get constraint condition
    bool GetConstr(const QString strFilePath, TableEntity *te);
private:
    QByteArray ba;
};

#endif // TABLEDATAOPS_H
