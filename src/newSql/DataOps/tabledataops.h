#ifndef TABLEDATAOPS_H
#define TABLEDATAOPS_H
#include ".\Entity\TableEntity.h"
#include ".\Entity\FieldEntity.h"
#include ".\Util\Appexception.h"
#include ".\Entity\RecordEntity.h"
#include ".\DataOps\recorddataops.h"
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
    bool AlterTable(const QString strFilePath, TABLEARR& tba);
    // Alert table name
    bool AlterTableName(const QString strFilePath, const QString DirFile,TableEntity * te,TABLEARR& tba);
    // Get constraint condition
    bool GetConstr(const QString strFilePath, TableEntity *te);
    bool AlterField(TableEntity *te,FieldEntity oldfield,FieldEntity newfield);
    bool delField(QString fieldName,int param,const QString tbfile,TableEntity *te,RECORDARR &arrRe);
    bool delTable(TABLEARR &arrtab,const QString tbFilePath,const QString DirPath);
    bool ModifyConstr(const QString strFilePath, TableEntity *te);
private:
    QByteArray ba;
};

#endif // TABLEDATAOPS_H
