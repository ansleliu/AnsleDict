#ifndef USERMGR_H
#define USERMGR_H
#include "MySQLite.h"
#include "QSettings"
#include "QStringList"

typedef QList< QMap<QString, QVariant> > LISTMAPINFO;
class UserMgr : public MySQLite
{
public:
    UserMgr(const QString &dbpath, const QString &connName,const QString &path);
    ~UserMgr();

public:
    bool exists(const QString &userName); // 判断用户是否存在
    QVariant getUserInfo(const QString &itemName,const QString &userName); // 获取用户相关的信息

    QStringList getUserList();	// 返回用户列表,已经按最后登录时间排序好
    QStringList getUserListOrderById();	// 返回用户列表, 按id降序排号

    void initMainConfig();
    QSettings *getCfg();

    QString getDefaultUser();
    void setDefaultUser(const QString &userName);

    bool getAutoSelect();
    void setAutoSelect(bool bAuto);


private:
    LISTMAPINFO getLMI(const QString & prefix);
    void setLMI(const QString & prefix, LISTMAPINFO &lmi);

private:
    QSettings *cfg;
};

#endif // USERMGR_H
