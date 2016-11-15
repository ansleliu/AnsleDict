#ifndef DICTMAINWINDOW_H
#define DICTMAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include "MyDictList.h"
#include "CreatWordListDB.h"
#include "QSystemTrayIcon"
#include "SpeakMgr.h"
#include "ConfigFile.h"

namespace Ui {
class DictMainWindow;
}

class DictMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DictMainWindow(QWidget *parent = 0);
    ~DictMainWindow();
    
private slots:
    void on_action_Add_triggered();

    void on_action_Delete_triggered();

    void on_action_Config_triggered();

    void on_action_Mini_triggered();

    void on_action_quit_triggered();

    void on_action_NomWindow_triggered();

    void on_action_Max_triggered();

    void on_action_Qt_triggered();

    void on_action_About_triggered();

    void on_DictComboBox_currentIndexChanged(const QString &dictname);

    void on_WordLineEdit_textChanged(const QString &word);

    void on_action_AddToNewWord_triggered();

    void on_WordTableView_clicked(const QModelIndex &index);

    void trayiconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_WordTableView_customContextMenuRequested(const QPoint &pos);

    void on_action_Speak_triggered();

    void setButtonState();

    void on_ExpComboBox_currentIndexChanged(int index);

    ////////////////////////////////////////////////////////
    //默认用户选择和更改
    void userSelect();

protected:
    void dictListShow();

private:
    Ui::DictMainWindow *ui;
    QSystemTrayIcon *trayIcon;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QMenu   *trayIconMenu;
    /////////////////////////////////
    //
    ConfigFile *speakConfig;

    /////////////////////////////////
    //
    MyDictList *MyDictListDB;
    QString defaultUser;
    //////////////////////////////
    //
    QString currDictPath;
    QString currDictName;
    CreatWordListDB *myDict;
    CreatWordListDB *myBook;
    QSqlTableModel *model;
    //////////////////////////////
    //
    SpeakMgr *speakMgr;
};

#endif // DICTMAINWINDOW_H
