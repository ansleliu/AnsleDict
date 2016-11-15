#ifndef MYDICTLIST_H
#define MYDICTLIST_H
#include "MySQLite.h"

class MyDictList : public MySQLite
{
public:
    MyDictList(const QString &dbpath, const QString &connName);
    ~MyDictList();

public:
    bool dictEixst(const QString &dictPath);

    bool addNewDict(const QString &dictName,
                    const QString &dictPath);
    bool deleteDict(const QString &dictPath);

    QString getDictName(const int &id);

    QString getDictPath(const int &id);
    QString getDictPath(const QString & dictName);

    QStringList getDictNames();
    QStringList getDictPaths();

protected:
    bool createTable();	// ´´½¨±í

private:


};

#endif // MYDICTLIST_H
