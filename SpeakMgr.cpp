#include "SpeakMgr.h"
#include <QDebug>
SpeakMgr::SpeakMgr(ConfigFile *config, QObject *parent) :
    QObject(parent)
{
    ///////////////////////////////////////////////
    //��Ƶ�ź��������
    ///////////////////////////////////////////////
    //eSpeakTTS
    sound = new SoundTread();
    connect(sound,SIGNAL(soundEnded()),
            this,SLOT(EmitSpeakFininshSignal()));
    ///////////////////////////////////////////////
    //GoogleTTS
    speakGoogleTTS = new SpeakGoogle();
    connect(speakGoogleTTS,SIGNAL(soundEnded()),
            this,SLOT(EmitSpeakFininshSignal()));
    connect(speakGoogleTTS,SIGNAL(speakError()),
            this,SLOT(changeSpeakEngineToESpeak()));
    ////////////////////////////////////////////////
    //��ȡ������������
    speakMethod = config->getSpeakMethod();
    ///////////////////////////////////////
    //QtSpeech
    QtSpeakTTS = NULL;
    if(speakMethod == "OtherTTS")
    {
        otherTTS = config->getQtSpeakTTS();
        qDebug() << QString("��������������Ϊ��%1").arg(otherTTS);
        ///////////////////////////////////
        //QtSpeech
        foreach(QtSpeech::VoiceName v, QtSpeech::voices())
        {
            qDebug() << "id:" << v.id;
            qDebug() << "name:" << v.name;
            if(v.name == otherTTS)
            {
                qDebug() << QString("�ҵ�ƥ��ķ������棺%1").arg(v.name);

                QtSpeakTTS = new QtSpeech(v,this);
                qDebug() << QString("����QtSpeech�����ɹ�");

                QtSpeakTTS->setRate(config->getSpeakSpeed().toInt());
                break;
            }
        }
    }
}

SpeakMgr::~SpeakMgr()
{
    sound->deleteLater();
    speakGoogleTTS->deleteLater();
    if(QtSpeakTTS != NULL)
    {
        QtSpeakTTS->deleteLater();
        QtSpeakTTS = NULL;
        qDebug() << QString("���QtSpeech�����ɹ�");
    }
}

void SpeakMgr::Speak(const QString &text,
                     const int &speakInterval,
                     const int &SpeakRepetitions)
{
    textSpeak = text;
    Interval = speakInterval;
    Repetitions = SpeakRepetitions;
    /////////////////////////////////////////
    //eSpeakTTS
    if(speakMethod == "eSpeakTTS")
    {
        qDebug() << "Ĭ������Ϊ��eSpeakTTS , ��ʼ����";
        sound->getSoundTime(Repetitions);
        sound->getWord(textSpeak);
        sound->getTimeDiff(Interval);
        sound->start();
    }
    //////////////////////////////////////////
    //googleTTS
    if(speakMethod == "GoogleTTS")
    {
        qDebug() << "Ĭ������Ϊ��GoogleTTS , ��ʼ����";
        speakGoogleTTS->setSoundTime(Repetitions);
        speakGoogleTTS->speakGoogleTTS(textSpeak);
    }
    /////////////////////////////////////////////////
    //OtherTTS
    if(speakMethod == "OtherTTS")
    {
        qDebug() << "Ĭ������Ϊ��OtherTTS , ��ʼ����";
        QtSpeakTTS->tell(textSpeak,this,SLOT(EmitSpeakFininshSignal()));
    }
}

void SpeakMgr::Stop()
{

}

void SpeakMgr::changeSpeakEngineToESpeak()
{
//    qDebug() << "ת��������ʽΪ��eSpeakTTS";
//    sound->getSoundTime(Repetitions);
//    sound->getWord(textSpeak);
//    sound->getTimeDiff(Interval);
//    sound->start();
    qDebug() << "ת��������ʽΪ��OtherTTS , ��ʼ����";
    QtSpeakTTS->tell(textSpeak,this,SLOT(EmitSpeakFininshSignal()));
}

void SpeakMgr::EmitSpeakFininshSignal()
{
    emit SpeakFininshed();
}
