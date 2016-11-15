#include "ConfigDialog.h"
#include "ui_ConfigDialog.h"
#include "QDebug"

ConfigDialog::ConfigDialog(QWidget *parent, ConfigFile *config) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    otherTTSInit();
    /////////////////////////////////////////////////////
    //
    speakConfig = config;
    speakMethode = speakConfig->getSpeakMethod();
    if(speakMethode == "eSpeakTTS")
    {
        qDebug() << QString("默认的发音引擎为：%1").arg(speakMethode);
        ui->ESpeakTTSRadioButton->setChecked(true);
    }
    else if(speakMethode == "GoogleTTS")
    {
        qDebug() << QString("默认的发音引擎为：%1").arg(speakMethode);
        ui->GoogleTTSRadioButton->setChecked(true);
    }
    else if(speakMethode == "OtherTTS")
    {
        qDebug() << QString("默认的发音引擎为：%1").arg(speakMethode);
        ui->OtherRadioButton->setChecked(true);
        QtSpeakTTS = speakConfig->getQtSpeakTTS();
        qDebug() << QString("第三方发音引擎为：%1").arg(QtSpeakTTS);
        initTTSCombox();
        if(QtSpeakTTS != "")
        {
            QtSpeakTTSID = ui->TTSComboBox->findText(QtSpeakTTS);
            qDebug() << QString("第三方发音引擎的ID为: %1").arg(QtSpeakTTSID);
            ui->TTSComboBox->setCurrentIndex(QtSpeakTTSID);
            qDebug() << QString("设置下拉选择框的当前索引值为: %1").arg(QtSpeakTTSID);
            ui->RateHorizontalSlider->setValue(config->getSpeakSpeed().toInt());
        }
    }
    else
    {
        qDebug() << QString("无法读取发音方法配置信息");
    }
}

ConfigDialog::~ConfigDialog()
{
    speakConfig = NULL;
    delete ui;
}

void ConfigDialog::initTTSCombox()
{
    ui->TTSComboBox->setEnabled(true);
    ui->RateHorizontalSlider->setEnabled(true);

    ////////////////////////////////////////////////////
    //
    foreach(QtSpeech::VoiceName v, QtSpeech::voices())
    {
        qDebug() << "id:" << v.id;
        qDebug() << "name:" << v.name;
 //       if(v.name == QtSpeakTTS)
 //       {
 //           QtSpeakTTSID = v.id.toInt();
 //           qDebug() << QString("第三方发音引擎的ID为: %1").arg(QtSpeakTTSID);
 //       }
        if(v.name == QString("Microsoft Mary") ||
                v.name == QString("Microsoft Mike") ||
                v.name == QString("Sample TTS Voice"))
        {
            qDebug() << QString("忽略Microsoft Mary , Microsoft Mike 和 Sample TTS Voice");
            qDebug() << QString("忽略: %1 成功").arg(v.name);
        }
        else
        {
            ui->TTSComboBox->addItem(v.name);
        }
    }
}

void ConfigDialog::otherTTSInit()
{
    ui->TTSComboBox->setEnabled(false);
    ui->RateHorizontalSlider->setEnabled(false);
}

void ConfigDialog::on_ApplyButton_clicked()
{
    if(ui->GoogleTTSRadioButton->isChecked())
    {
        speakConfig->setSpeakMethod(QString("GoogleTTS"));
    }
    if(ui->ESpeakTTSRadioButton->isChecked())
    {
        speakConfig->setSpeakMethod(QString("eSpeakTTS"));
    }
    if(ui->OtherRadioButton->isChecked())
    {
        speakConfig->setSpeakMethod(QString("OtherTTS"));
        qDebug() << QString("第三方发音引擎成功设为：%1").arg(ui->TTSComboBox->currentText());
        speakConfig->setQtSpeakTTS(ui->TTSComboBox->currentText());
        qDebug() << QString("第三方发音引擎发音速度成功设为：%1").arg(ui->RateHorizontalSlider->value());
        speakConfig->setSpeakSpeed(QString::number(ui->RateHorizontalSlider->value(),'i',0));

    }
    accept();
}

void ConfigDialog::on_CancelButton_clicked()
{
    reject();
}

QString ConfigDialog::voiceMethode()
{
    if(ui->GoogleTTSRadioButton->isChecked())
    {
        return QString("GoogleTTS");
    }
    if(ui->ESpeakTTSRadioButton->isChecked())
    {
        return QString("eSpeakTTS");
    }
    return QString("eSpeakTTS");
}

void ConfigDialog::on_ESpeakTTSRadioButton_clicked(bool checked)
{
    if(checked == true)
    {
        qDebug() << QString("选择eSpeakTTS");
        otherTTSInit();
    }
}

void ConfigDialog::on_GoogleTTSRadioButton_clicked(bool checked)
{
    if(checked == true)
    {
        qDebug() << QString("选择GoogleTTS");
        otherTTSInit();
    }
}

void ConfigDialog::on_OtherRadioButton_clicked(bool checked)
{
    if(checked == true)
    {
        qDebug() << QString("选择OtherTTS");
        initTTSCombox();
    }
}

void ConfigDialog::on_RateHorizontalSlider_valueChanged(int value)
{
    qDebug() << QString("当前的放音速度为：%1").arg(value);
}
