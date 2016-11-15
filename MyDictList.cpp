#include "MyDictList.h"

MyDictList::MyDictList(const QString &dbpath, const QString &connName)
    : MySQLite(dbpath, connName)
{
    if (!isTableExist("MyDictList"))	// 新建的数据库,创建表
    {
        createTable();
    }
}

MyDictList::~MyDictList()
{

}

bool MyDictList::dictEixst(const QString &dictPath)
{
    QSqlQuery query(QString("select id from MyDictList where DictPath = '%1'").arg(dictPath), *db);
    return query.next();
}

bool MyDictList::addNewDict(const QString &dictName,
                            const QString &dictPath)
{
    if (!dictEixst(dictPath))
    {
        QString sql = QString("insert into MyDictList(DictName, DictPath) values('%1', '%2')")
            .arg(dictName)
            .arg(dictPath);

        return exec(sql);
    }
    else
    {
        return false;
    }
}

bool MyDictList::deleteDict(const QString &dictPath)
{
    if(dictEixst(dictPath))
    {
        QString sql = QString("delete from MyDictList where DictPath = '%1'")
            .arg(dictPath);
        return exec(sql);
    }
    else
    {
        return false;
    }
}

QString MyDictList::getDictName(const int &id)
{
    QSqlQuery query(QString("select DictName from MyDictList where id = '%1'").arg(id), *db);
    query.next();
    return query.record().value(0).toString();
}

QString MyDictList::getDictPath(const int &id)
{
    QSqlQuery query(QString("select DictPath from MyDictList where id = '%1'").arg(id), *db);
    query.next();
    return query.record().value(0).toString();
}

QString MyDictList::getDictPath(const QString &dictName)
{
    QSqlQuery query(QString("select DictPath from MyDictList where DictName = '%1'").arg(dictName), *db);
    query.next();
    return query.record().value(0).toString();
}

QStringList MyDictList::getDictNames()
{
    QStringList dictNames;
    QSqlQuery query("select DictName from MyDictList", *db);
    while (query.next())
    {
        dictNames << query.record().value("DictName").toString();
    }
    return dictNames;
}

QStringList MyDictList::getDictPaths()
{
    QStringList dictPaths;
    QSqlQuery query("select DictPath from MyDictList", *db);
    while (query.next())
    {
        dictPaths << query.record().value("DictPath").toString();
    }
    return dictPaths;
}

bool MyDictList::createTable()
{
    QSqlQuery query(*db);

    query.exec("CREATE TABLE [MyDictList] (\
               [id] INTEGER NOT NULL ON CONFLICT FAIL PRIMARY KEY AUTOINCREMENT, \
               [DictName] TEXT NOT NULL ON CONFLICT FAIL, \
               [DictPath] TEXT NOT NULL ON CONFLICT FAIL);");

    db->commit();

    return true;
}
