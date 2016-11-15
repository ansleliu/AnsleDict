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
    bool exists(const QString &userName); // �ж��û��Ƿ����
    QVariant getUserInfo(const QString &itemName,const QString &userName); // ��ȡ�û���ص���Ϣ

    QStringList getUserList();	// �����û��б�,�Ѿ�������¼ʱ�������
    QStringList getUserListOrderById();	// �����û��б�, ��id�����ź�

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
