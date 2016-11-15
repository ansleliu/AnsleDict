#ifndef THREAD_H
#define THREAD_H
#include "QThread"
#include "../SpeakTTS.h"
class SoundTread : public QThread
{
    Q_OBJECT
public:
    SoundTread(QObject* parent=0)
        :QThread(parent)
    {
        //////////////////////////////
        //
        eSpeakTTS = new SpeakTTS();
        //获取发音参数
        speed = QString::number(200,'i',0);
        volume = QString::number(100,'i',0);
        pitch = QString::number(50,'i',0);
        pitchRange = QString::number(50,'i',0);
        wordGap = QString::number(0,'i',0);
        ///////////////////////////////////
        //
        stopped = false;
    }
    ~SoundTread()
    {
        eSpeakTTS->stopSpeakTTS();
        eSpeakTTS->deleteLater();
    }
public slots:

signals:
    void soundEnded();

protected:
    virtual void run ()
    {
        if(!stopped)
        {
            while(soundTime > 0)
            {         
                //////////////////////
                //TTS发音
                eSpeakTTS->stopSpeakTTS();

                eSpeakTTS->initESpeaktts();//初始化TTS
                eSpeakTTS->setSpeakLanguage("de");//设置语言
                eSpeakTTS->setSpeakSpeed(speed.toInt());//音速设定
                eSpeakTTS->setSpeakVolume(volume.toInt());//音量设定
                eSpeakTTS->setSpeakPitch(pitch.toInt(),pitchRange.toInt());//音调设定
                eSpeakTTS->setSpeakWordGap(wordGap.toInt());//间隔设定
                eSpeakTTS->speakTTS(text);//发音

                //////////////////////////////////////////
                //
                soundTime--;
                if(soundTime != 0)
                {
                    msleep(timeDiff);
                }
                else
                {
                    emit soundEnded();
                }
            }
        }
    }

public:
    ////////////////////////
    //
    virtual void stop()
    {
        stopped = true;
        eSpeakTTS->stopSpeakTTS();
    }
    ///////////////////////////////////////////
    //
    virtual void getWord(const QString &word)
    {
        text = word;
    }
    ////////////////////////////////////////////
    //
    virtual void getSoundTime(const int &time)
    {
        soundTime = time;
    }
    ///////////////////////////////////////////////
    //
    virtual void getTimeDiff(const int &timediff)
    {
        timeDiff = timediff;
    }

private:
    volatile bool stopped;
    QString text;
    volatile int soundTime;
    volatile int timeDiff;

    SpeakTTS *eSpeakTTS;
    QString speed;
    QString volume;
    QString pitch;
    QString pitchRange;
    QString wordGap;
};
////////////////////////////////////////////////////////////////////////////////
//
#endif // THREAD_H
