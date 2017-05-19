#ifndef RECORDENTITY_H
#define RECORDENTITY_H
#include "./Global/ref.h"
#include"./Global/datastructure.h"
class RecordEntity
{
public:
    // Constructor
    RecordEntity();
    // Copy constructor
    RecordEntity(RecordEntity &e);
    // Destructor
    ~RecordEntity();

    // Overload "=" operator
    RecordEntity &operator =(const RecordEntity &);

public:
    // Save the value of the field
    void Put(QString strFieldName, QString strValue);
    void Put(QString strFieldName, int nValue);
    void Put(QString strFieldName, double dbValue);
    void Put(QString strFieldName, QDateTime t);
    QHash<QString, QString>& getReArr();
    // Get the value of the field.
    QString Get(QString strFieldName);

private:
    QHash<QString, QString> m_mapData; // Data
    QHash<QString, QString>::const_iterator i;
};
typedef QHash<int, RecordEntity*> RECORDARR;
#endif // RECORDENTITY_H
