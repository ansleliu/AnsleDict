#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include "ConfigFile.h"
#include "QtSpeech.h"

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfigDialog(QWidget *parent = 0,ConfigFile *config = NULL);
    ~ConfigDialog();
    
private slots:
    void on_ApplyButton_clicked();

    void on_CancelButton_clicked();

    void on_ESpeakTTSRadioButton_clicked(bool checked);

    void on_GoogleTTSRadioButton_clicked(bool checked);

    void on_OtherRadioButton_clicked(bool checked);

    void on_RateHorizontalSlider_valueChanged(int value);

public:
    QString voiceMethode();
    void initTTSCombox();
    void otherTTSInit();

private:
    Ui::ConfigDialog *ui;
    ConfigFile *speakConfig;
    QString speakMethode;
    QString QtSpeakTTS;
    int QtSpeakTTSID;
};

#endif // CONFIGDIALOG_H
