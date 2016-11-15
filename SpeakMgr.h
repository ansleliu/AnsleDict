#ifndef SPEAKMGR_H
#define SPEAKMGR_H

#include <QObject>
#include "SpeakGoogle.h"
#include "Thread/thread.h"
#include "QtSpeech.h"
#include "ConfigFile.h"
//////////////////////////////////////////
//
class SpeakMgr : public QObject
{
    Q_OBJECT
public:
    explicit SpeakMgr(ConfigFile *config, QObject *parent = 0);
    ~SpeakMgr();

public:
    void Speak(const QString &text,
               const int &speakInterval,
               const int &SpeakRepetitions);
    void Stop();

private slots:
    void changeSpeakEngineToESpeak();

signals:
    void SpeakFininshed();

public slots:
    void EmitSpeakFininshSignal();

private:
    SoundTread *sound;//eSpeakTTS
    SpeakGoogle *speakGoogleTTS;//GoogleTTS
    QtSpeech *QtSpeakTTS;//QtSpeakTTS

    QString speakMethod;//∑¢“Ù∑Ω∑®
    QString speakRate;
    QString otherTTS;

    QString textSpeak;

    int Interval;
    int Repetitions;
};

#endif // SPEAKMGR_H
