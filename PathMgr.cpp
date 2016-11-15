#include "PathMgr.h"
#include <QFile>

PathManage::PathManage()
{
}

QString PathManage::makePathStr(const QString &fileName)
{
    QString appPath = QCoreApplication::applicationDirPath();
    //��pathName����ġ�/���ָ���ת��Ϊ�����ڵײ����ϵͳ�ķָ���������ת�����ַ�����
    return QDir::convertSeparators(appPath.append(fileName));
}

void PathManage::mkPath(const QString &strPath)
{
    if (!QDir(strPath).exists())
    {
        QDir().mkpath(strPath);
    }
}

void PathManage::createRelExeDir(const QString &path)
{
    QString strPath = PathManage::makePathStr(path);
    PathManage::mkPath(strPath);
}

QString PathManage::makeRelativeFilePath(const QString &fileName)
{
    QDir dirfrom;
    return dirfrom.relativeFilePath(makePathStr(fileName));
}

bool PathManage::saveToDisk(const QString &filename, QIODevice *data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        fprintf(stderr, "Could not open %s for writing: %s\n",
            qPrintable(filename),
            qPrintable(file.errorString()));
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}

bool PathManage::saveToDisk(const QString &filename, QByteArray &data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        fprintf(stderr, "Could not open %s for writing: %s\n",
            qPrintable(filename),
            qPrintable(file.errorString()));
        return false;
    }

    file.write(data);
    file.close();

    return true;
}
