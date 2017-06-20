#ifndef SERVICE_H
#define SERVICE_H
#include"./Entity/tableentity.h"
#include"./Entity/dbentity.h"
#include"./Entity/recordentity.h"
#include"./Entity/dbentity.h"
#include "qdebug.h"
class service
{
public:
    service();
    ~service(void);

public:
    DBEntity* m_dbEntity;	// 当前操作的数据库
    QString m_strError;		// 错误信息
    TableEntity* m_tbEntity;	// 当前操作的表
    RECORDARR m_arrRecord;	// 存放记录的Hash
    DBARR m_arrDB; // 存放所有数据库的Hash

public:
    QString GetError();					//	获取异常错误信息
    void SetError(QString strError);	//	设置异常错误信息

    void SetCurDB(QString strDBName); // 设置当前操作的数据库
    void SetCurTable(QString strTableName);		// 设置当前操作的表
    // 数据库操作
    DBEntity *GetCurDB();
    bool CreateDatabase(QString dbname);
    bool RenameDatabase(QString oldDBname,QString newDBname);
    bool DeleteDatabase(QString dbName);
    // 表操作
    TableEntity* GetCurTable();
    TableEntity* CreateTable(QString strDBName,QString strName);		// 创建表
    TableEntity* GetTable(int nIndex);				// 获取表实体组中第几个表
    bool DeleteTable(QString tbName,QString DBname);
    bool ReNameTable(QString DBName,QString oldName,QString newName);
    // 字段操作
    FieldEntity* AddField(QString strDBName,QString strTBName,FieldEntity &field);	// 添加字段
    bool DeleteField(QString tbName,QString DBname,QString fieldName);
    bool ModifyField(QString tbName,QString DBname,QString fieldName,FieldEntity* newField);
    bool ModifyField(QString tbName,QString DBname,QString fieldName,QString newName);
    // 记录操作
    RecordEntity* InsertRecord(QString strDBName,QString strTBName,RecordEntity &record);	// 插入记录
    int GetRecordNum();								// 获取当前记录表中的数目
    RecordEntity* GetRecord(int nIndex);			// 获取第几条记录
    void LoadRecord(QString strDBName,QString strTBName); // 获取指定数据库指定表的记录信息
    void cleanRecordArr();// 清空当前记录数组
    bool queryOne(QString DBName,QString TBName,SEARCHARRAY search_arr);
    // 获取各QHash
    QHash<int, DBEntity *> & getDBArr();
    QHash<int, RecordEntity *> & getRecordArr();

    QList<QString> getUN(QString DBName,QString TBName);
    QList<QString> getNN(QString DBName,QString TBName);

    // 将改变后的记录写入文件
    bool changeRecordToFile(QString DBName,QString TBName);
    // 获取表中主键
    QString getPri(QString DBName,QString TBName);
    // 判断数据库名字是否重复
    bool checkDBName(QString DBName);
    // 判断表名字是否重复
    bool checkTBName(QString DBName,QString TBName);
    // 判断字段名字是否重复
    bool checkFDName(QString DBName,QString TBName,QString FDName);
    void CleanContainer();// 清空各个Hash中的数据,应该与CleanContainer搭配使用
    void LoadAllInfo();// 读取数据到各个Hash中,应该与CleanContainer搭配使用
    void getQR(QHash<int,RecordEntity *> QR);
private:
    void LoadTables(DBEntity* db);			   // 读取指定数据库的表到其中的Hash
};

#endif // SERVICE_H
