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

    //ÐÞ¸ÄºÍÉ¾³ý¼ÇÂ¼
    bool ModifyAndDelete(TableEntity &te, RECORDARR &arrRe);

public:
    // Save record
    bool Write(QTextStream &out, TableEntity *te, RecordEntity *re);
    // Get record
    bool Read(QTextStream &in
              , TableEntity &te, RecordEntity &re);

    QByteArray ba;
    bool ok;
};

#endif // RECORDDATAOPS_H
