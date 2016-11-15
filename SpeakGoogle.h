#ifndef SPEAKGOOGLE_H
#define SPEAKGOOGLE_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include "./DownloadControl/DownloadControl.h"
#include "phonon"
#include <QUrl>
#include <QFile>
#include <QTime>

class SpeakGoogle : public QObject
{
    Q_OBJECT
public:
    explicit SpeakGoogle(QObject *parent = 0);
    ~SpeakGoogle();
    
signals:
    void soundEnded();
    void speakError();

public slots:
    void NetWorkIsBad();

    void stateChanged(Phonon::State newState,
                      Phonon::State oldstate);
    void startSpeak();
    void googleTTS();
    void setSoundTime(const int &soundtime);

    void speakGoogleTTS(const QString &text);
    void speakGoogleRestart();
    void googleTTSPlay();
    void googleTTSStop();

    Phonon::MediaObject *getMediaObject();

private:
    QUrl myurl;   //´æ´¢ÍøÂçµØÖ·

    QTime starttime;

    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;
    Phonon::State curState;

    int soundTime;
    int time;
    QString wordText;
};

#endif // SPEAKGOOGLE_H
