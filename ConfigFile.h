#ifndef CONFIGFILE_H
#define CONFIGFILE_H
#include "QSettings"

typedef QList< QMap<QString, QVariant> > LISTMAPINFO;
class ConfigFile
{
public:
    ConfigFile(const QString &path);
    ~ConfigFile();

public:
    void initMainConfig();
    ///////////////////////////////////////////////////////////////////
    //��ȡ��������
    QString getSpeakMethod()
    {
        return cfg->value("SpeakTTS/SpeakMethod", "eSpeakTTS").toString();
    }
    void setSpeakMethod(const QString &speakMethod)
    {
        cfg->setValue("SpeakTTS/SpeakMethod", speakMethod);
    }

    ///////////////////////////////////////////////////////////////////
    //��ȡ�������������淽
    QString getQtSpeakTTS()
    {
        return cfg->value("SpeakTTS/QtSpeakTTS", "").toString();
    }
    void setQtSpeakTTS(const QString &QtSpeakTTS)
    {
        cfg->setValue("SpeakTTS/QtSpeakTTS", QtSpeakTTS);
    }

    ///////////////////////////////////////////////////////////////////
    //SpeakTTS
    ///////////////////////
    //���ٵ��ڼ�¼
    QString getSpeakSpeed()
    {
        return cfg->value("SpeakTTS/SpeackRate", "0").toString();
    }
    void setSpeakSpeed(const QString &speakSpeed)
    {
        cfg->setValue("SpeakTTS/SpeackRate", speakSpeed);
    }

private:
    LISTMAPINFO getLMI(const QString & prefix);
    void setLMI(const QString & prefix, LISTMAPINFO &lmi);

private:
    QSettings *cfg;
};

#endif // CONFIGFILE_H
