#ifndef SPEAKTTS_H
#define SPEAKTTS_H

#include <QObject>
#include <QByteArray>
//������C���dll�ļ�����C++��������ͷ�ļ�Ҫ��extern "C" {}
extern "C"
{
    #include "eSpeak/speak_lib.h"
}

class SpeakTTS : public QObject
{
    Q_OBJECT
public:
    explicit SpeakTTS(QObject *parent = 0);
    void initESpeaktts();
    void setSpeakSpeed(const int &speed);
    void setSpeakVolume(const int &volume);
    void setSpeakPitch(const int &pitch,const int &range);
    void setSpeakWordGap(const int &wordgap);
    void setSpeakLanguage(const char *language);

    void speakTTS(const QString &text);

    bool isSpeakTTSPlaying();
    void stopSpeakTTS();
    
signals:
    
public slots:
    
};

#endif // SPEAKTTS_H
