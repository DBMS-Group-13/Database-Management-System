#ifndef RECORDDATAOPS_H
#define RECORDDATAOPS_H
#include ".\Entity\tableentity.h"
#include ".\Entity\Recordentity.h"
#include ".\Util\Appexception.h"
#include<qexception.h>
#include <qtextstream.h>
#include <qdatastream.h>
#include <QTextCodec>
#include <QFile>
class RecordDataOps
{
public:
    RecordDataOps();
    // Create new rows in a table
    bool Insert(TableEntity &te, RecordEntity &re);
    // Retrieve all records from a specified table
    int SelectAll(TableEntity &te, RECORDARR &data);
    //修改和删除记录
    bool ModifyAndDelete(const QString tbfile,TableEntity &te, RECORDARR &arrRe);
    bool SelectOne(FieldEntity filed,QString value,TableEntity &te, RecordEntity &re);
    bool Select(SEARCHARRAY search_arr,TableEntity &te, RECORDARR &reArr);
    bool Compare(SEARCHARRAY search_arr,TableEntity &te,RecordEntity &re);
public:
    // Save record
    bool Write(QTextStream &out, TableEntity *te, RecordEntity *re);
    // Get record
    bool Read(QTextStream &in
              , TableEntity &te, RecordEntity &re);

    bool ok;
};

#endif // RECORDDATAOPS_HPS_H

