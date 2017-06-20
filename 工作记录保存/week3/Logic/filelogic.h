#ifndef FILELOGIC_H
#define FILELOGIC_H
#include "./Global/ref.h"
#include <QDir>

class FileLogic
{
public:
    // Get the path of the database description file
    QString GetDBFile(void);
    // Get the path of the database folder
    QString GetDBFolder(const QString strDBName);
    // Get the path of the database table description file
    QString GetTableFile(const QString strDBName);
    // Get the path of the table definition file
    QString GetTbDefineFile(const QString strDBName, const QString strTableName);
    // Get the path of the table record file
    QString GetTbRecordFile(const QString strDBName, const QString strTableName);
    // Get the path of the table restraint file
    QString GetTbConstrFile(const QString strDBName, const QString strTableName);
    //删除文件目录
    bool DeleteDirectory(const QString &path);

public:
    // Change relative path into an absolute path.
    QString GetAbsolutePath(const QString strRelativePath);
};

#endif // FILELOGIC_H
