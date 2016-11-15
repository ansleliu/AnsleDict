#include "UserMgr.h"
#include "QSqlQuery"
#include "QFile"
#include "QFileInfo"

UserMgr::UserMgr(const QString &dbpath, const QString &connName, const QString &path)
    : MySQLite(dbpath, connName)
{
    bool isExists = QFile::exists(path);
    cfg = new QSettings(path, QSettings::IniFormat);
    cfg->setIniCodec("GB18030");
    if (!isExists)
    {
        QFileInfo fd(path);
        QString configName = fd.baseName();
        if(configName == "Config")
        {
            initMainConfig();
        }
    }
}

UserMgr::~UserMgr()
{
    delete cfg;
    cfg = NULL;
}

bool UserMgr::exists(const QString &userName)
{
    QSqlQuery query(QString("select id from UserInfo where userName = '%1'").arg(userName), *db);
    return query.next();
}

QVariant UserMgr::getUserInfo(const QString &itemName, const QString &userName)
{
    if (exists(userName))
    {
        QSqlQuery query(QString("select * from UserInfo where userName = '%1'").arg(userName), *db);
        query.next();
        return query.record().value(itemName);
    }
    else
    {
        return NULL;
    }
}

QStringList UserMgr::getUserList()
{
    QStringList orderResult;
    QSqlQuery query("select userName from UserInfo order by lastLoginTime desc", *db);
    while (query.next())
    {
        orderResult << query.record().value("userName").toString();
    }

    return orderResult;
}

QStringList UserMgr::getUserListOrderById()
{
    QStringList orderResult;
    QSqlQuery query("select userName from UserInfo order by id desc", *db);
    while (query.next())
    {
        orderResult << query.record().value("userName").toString();
    }

    return orderResult;
}

void UserMgr::initMainConfig()
{
    LISTMAPINFO LMI_DefaultUser;
    QMap<QString, QVariant> DefaultUserConfig;
    DefaultUserConfig["DefaultUser"] = "default";
    DefaultUserConfig["AutoSelect"] = false;
    LMI_DefaultUser << DefaultUserConfig;
    setLMI("DefaultUserConfig", LMI_DefaultUser);
}

QSettings *UserMgr::getCfg()
{
    return cfg;
}

QString UserMgr::getDefaultUser()
{
    return cfg->value("DefaultUserConfig/DefaultUser", "default").toString();
}

void UserMgr::setDefaultUser(const QString &userName)
{
    cfg->setValue("DefaultUserConfig/DefaultUser", userName);
}

bool UserMgr::getAutoSelect()
{
    return cfg->value("DefaultUserConfig/AutoSelect", true).toBool();
}

void UserMgr::setAutoSelect(bool bAuto)
{
    cfg->setValue("DefaultUserConfig/AutoSelect", bAuto);
}

LISTMAPINFO UserMgr::getLMI(const QString &prefix)
{
    LISTMAPINFO result;
    int size = cfg->beginReadArray(prefix);
    for(int i = 0; i < size; i++)
    {
        cfg->setArrayIndex(i);
        QStringList keys = cfg->childKeys();
        QMap<QString, QVariant> learnWordConfig;
        for(int j = 0; j < keys.size(); j++)
        {
            learnWordConfig[keys[j]] = cfg->value(keys[j]).toString();
        }
        result << learnWordConfig;

    }
    cfg->endArray();
    return result;
}

void UserMgr::setLMI(const QString &prefix, LISTMAPINFO &lmi)
{
    cfg->beginWriteArray(prefix);
    for(int i = 0; i < lmi.size(); i++)
    {
//        cfg->setArrayIndex(i);
        QMapIterator<QString, QVariant> iter(lmi.at(i));
        while (iter.hasNext())
        {
            iter.next();
            cfg->setValue(iter.key(), iter.value());
        }
    }
    cfg->endArray();
}
