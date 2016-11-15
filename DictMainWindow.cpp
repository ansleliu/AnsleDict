#include "DictMainWindow.h"
#include "ui_DictMainWindow.h"
#include "PathMgr.h"
#include "AddDictDialog.h"
#include "DeleteDictDialog.h"
#include "ConfigDialog.h"
#include "QMessageBox"
#include "AboutDialog.h"
#include "QTableWidgetItem"
#include "UserSelectDialog.h"
#include "QTimer"
#include "QDebug"
////////////////////////////////////////////////////
//
DictMainWindow::DictMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DictMainWindow)
{
    ui->setupUi(this);
    ///////////////////////////////////////////////////////////////
    //
    QIcon icon = QIcon("./rc/Wordpress.ico");

    //创建托盘图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    QString titlec=tr("德语电子词典 -- AnsleDict");
    QString textc=tr("欢迎您使用德语电子词典 -- AnsleDict");
    ui->statusBar->showMessage(tr("欢迎您使用德语背单词软件德语电子词典！ -- ansleliu"));
    trayIcon->show();
    //弹出气泡提示
    trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);
    //添加单/双击鼠标相应
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
    //创建监听行为
    minimizeAction = new QAction(tr("最小化 (&I)"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    restoreAction = new QAction(tr("还原 (&R)"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("退出 (&Q)"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    //创建右键弹出菜单
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
    ///////////////////////////////////////////////////////////////////////////////////////
    //发音方法配置
    speakConfig = new ConfigFile(PathManage::makePathStr("/AnsleDict/speakConfig.ini"));
    //////////////////////////////////////////////////////////////////////
    //设置软件相关路径
    PathManage::createRelExeDir("/AnsleDict/MyDict/");
    PathManage::createRelExeDir("/AnsleDict/MyDict/Dict/");
//    PathManage::createRelExeDir("/AnsleDict/MyDict/我的生词本/");
    //创建我的生词本
    myBook = NULL;
    speakMgr = NULL;
//    QString myBookDB = PathManage::makePathStr("/AnsleDict/MyDict/我的生词本/我的生词本.db");
//    myBook = new CreatWordListDB(myBookDB,"MyBook");
    //创建词典列表数据库
    QString myDictDB = PathManage::makePathStr("/AnsleDict/MyDict/MyDictList.db");
    MyDictListDB = new MyDictList(myDictDB,"MyDictList");

    /////////////////////////////////////////////////
    //
    myDict = NULL;
    currDictPath = "";
    currDictName = "";
    //////////////////////////////////////////////////////////////
    //音频信号与槽连接
    ui->action_Speak->setEnabled(false);
    ui->action_AddToNewWord->setEnabled(false);
    speakMgr = NULL;

    model = NULL;
    ui->WordTableView->setUpdatesEnabled(true);

    dictListShow();
    ui->WordLineEdit->setFocus();

    ///////////////////////////////////////////////////////////////
    //默认用户选择
    defaultUser = "default";
    QTimer::singleShot(200, this, SLOT(userSelect()));
}

DictMainWindow::~DictMainWindow()
{
    if(model != NULL)
    {
        model->deleteLater();
        model = NULL;
    }
    delete MyDictListDB;
    MyDictListDB = NULL;

    if(myBook != NULL)
    {
        delete myBook;
        myBook = NULL;
    }

//    qDebug() << QString("删除myDict");
    if(myDict != NULL)
    {
        delete myDict;
        myDict = NULL;
    }
    if(speakMgr != NULL)
    {
        speakMgr->deleteLater();
        speakMgr = NULL;
    }
    delete ui;
}

void DictMainWindow::dictListShow()
{
    ui->DictComboBox->clear();
    QStringList dictList = MyDictListDB->getDictNames();
    QStringListIterator Iterator(dictList);
    //向combobox中添加单元
    while(Iterator.hasNext())
    {
        ui->DictComboBox->addItem(QIcon("./rc/Dots.ico"),Iterator.next());
    }
}

void DictMainWindow::userSelect()
{
    UserSelectDialog *user;
    user = new UserSelectDialog(this,false);

    if(user->exec() == QDialog::Accepted)
    {
        defaultUser = user->getDefaultUser();
        QString myBookDB = PathManage::makePathStr("/userdata/" + defaultUser + "/我的生词本/我的生词本.db");
        myBook = new CreatWordListDB(myBookDB,"MYBOOk");

        this->setWindowTitle(QString("AnsleDict -- 默认当前用户：%1").arg(defaultUser));
        user->close();
        user->deleteLater();
        user = NULL;
    }
    else
    {
        on_action_quit_triggered();
        user->close();
        user->deleteLater();
        user = NULL;
    }
}

void DictMainWindow::on_action_Add_triggered()
{
    AddDictDialog *AddDict;
    AddDict = new AddDictDialog(this);

    if(AddDict->exec() == QDialog::Accepted)
    {
        currDictPath = AddDict->getDictPath();
        currDictName = AddDict->getDictName();
        if(currDictPath == "" || currDictName == "")
        {
            qDebug() << QString("添加词典失败！");
        }
        else
        {
            MyDictListDB->addNewDict(currDictName,currDictPath);
            dictListShow();
        }
    }

    AddDict->close();
    AddDict->deleteLater();
    AddDict = NULL;

    ui->action_Speak->setEnabled(false);
    ui->action_AddToNewWord->setEnabled(false);
}

void DictMainWindow::on_action_Delete_triggered()
{
    DeleteDictDialog * deleteDict;
    deleteDict = new DeleteDictDialog(MyDictListDB,this);

    if(deleteDict->exec() == QDialog::Accepted)
    {
        dictListShow();
    }
    else
    {
        dictListShow();
    }
    deleteDict->close();
    deleteDict->deleteLater();
    deleteDict = NULL;

    ui->action_Speak->setEnabled(false);
    ui->action_AddToNewWord->setEnabled(false);
}

void DictMainWindow::on_action_Config_triggered()
{
    ConfigDialog * config;
    config = new ConfigDialog(this,speakConfig);

    if(config->exec() == QDialog::Accepted)
    {

    }
    config->close();
    config->deleteLater();
    config = NULL;
}

void DictMainWindow::on_action_Mini_triggered()
{
    this->hide();
}

void DictMainWindow::on_action_quit_triggered()
{
    if (QMessageBox::information(this, "提示信息", "您确定要退出吗?",
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        QApplication::closeAllWindows();
    }
    else
    {

    }
}

void DictMainWindow::on_action_NomWindow_triggered()
{
    this->showNormal();
}

void DictMainWindow::on_action_Max_triggered()
{
    this->showFullScreen();
}

void DictMainWindow::on_action_Qt_triggered()
{
    QApplication::aboutQt();
}

void DictMainWindow::on_action_About_triggered()
{
    AboutDialog *aboutD = new AboutDialog(this);
    if(aboutD->exec() == QDialog::Rejected)
    {

    }
    aboutD->close();
    aboutD->deleteLater();
    aboutD = NULL;
}

void DictMainWindow::on_DictComboBox_currentIndexChanged(const QString &dictname)
{
    ui->action_Speak->setEnabled(false);
    ui->action_AddToNewWord->setEnabled(false);
    if(dictname == "")
    {
        if(myDict != NULL)
        {
            delete myDict;
            myDict = NULL;
        }
        model = NULL;
        ui->MeanTextBrowser->clear();
        ui->WordLineEdit->clear();
    }
    else
    {
        ui->MeanTextBrowser->clear();
        ui->WordLineEdit->clear();
        QString dictPath = MyDictListDB->getDictPath(dictname);
        if(myDict != NULL)
        {
            delete myDict;
            myDict = NULL;
        }
        myDict = new CreatWordListDB(dictPath,"MyDict");

        model = NULL;
        model = myDict->wordListDBModel(this,"WordsBook");
        ui->WordTableView->setModel(model);
        ui->WordTableView->hideColumn(0);
        ui->WordTableView->hideColumn(2);
        ui->WordTableView->hideColumn(3);
        ui->WordTableView->hideColumn(4);
        model->select();
    }
}

void DictMainWindow::on_WordLineEdit_textChanged(const QString &word)
{
    ui->WordLineEdit->setFocus();
    ui->MeanTextBrowser->clear();
    ui->action_Speak->setEnabled(false);
    ui->action_AddToNewWord->setEnabled(false);
//    model->setFilter(QString("Wort like '%%1%'").arg(word));
    //显示结果
//    model->select();
    if(ui->ExpComboBox->currentIndex() == 0)
    {
        model->setFilter(QString("Wort like '%1%'").arg(word));
        //显示结果
        model->select();        
    }
    else if(ui->ExpComboBox->currentIndex() == 1)
    {
        model->setFilter(QString("Wort like '%%1%'").arg(word));
        //显示结果
        model->select();
    }
    else if(ui->ExpComboBox->currentIndex() == 2)
    {
        model->setFilter(QString("Wort like '%%1'").arg(word));
        //显示结果
        model->select();        
    }
}

void DictMainWindow::on_action_AddToNewWord_triggered()
{
    QModelIndex currIndex = ui->WordTableView->currentIndex();
    QString word = currIndex.data().toString();
    if(myBook->isExist(word))
    {
        QMessageBox::information(this, "提示信息", "该单词在生词本中已经存在,不必重复添加");
        ui->action_AddToNewWord->setEnabled(false);
    }
    else
    {
        int row = currIndex.row();
        QString mean = model->index(row,2).data().toString();
        int count = myBook->getRowCount();
        int lektion = (count+1)/200 + 1;
        myBook->addNewRecord(word,mean,"",lektion);
        ui->action_AddToNewWord->setEnabled(false);
    }
}


void DictMainWindow::on_WordTableView_clicked(const QModelIndex &index)
{
    ui->action_Speak->setEnabled(true);
//    QString word = index.data().toString();
    int row = index.row();

    QString mean = model->index(row,2).data().toString();

    ui->MeanTextBrowser->clear();
//    ui->WordLineEdit->setText(word);
    ui->MeanTextBrowser->setHtml(mean);
    ui->action_Speak->setEnabled(true);
    ui->action_AddToNewWord->setEnabled(true);
}

void DictMainWindow::trayiconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
            //单击托盘图标
            {
                if(this->isHidden())
                {
                    this->showNormal();
                    this->raise();
                    break;
                }
                else
                {
                    this->hide();
                    break;
                }
            }
        case QSystemTrayIcon::DoubleClick:
            //双击托盘图标
            {
                if(this->isHidden())
                {
                    this->showNormal();
                    this->raise();
                    break;
                }
                else
                {
                    this->hide();
                    break;
                }
            }
        default:
            break;
    }
}

void DictMainWindow::on_WordTableView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex currIndex = ui->WordTableView->indexAt(pos);
    //这种情况是右键的位置不在范围内，即在空白位置右击
    if(!currIndex.isValid())
    {

    }
    else
    {
        QMenu *popMenu =new QMenu(this);//定义一个右键弹出菜单
        popMenu->addAction(ui->action_AddToNewWord);
        popMenu->addAction(ui->action_Speak);

        popMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置

        delete popMenu;
        popMenu = NULL;
    }
}

void DictMainWindow::on_action_Speak_triggered()
{
    ui->action_Speak->setEnabled(false);
    QModelIndex currIndex = ui->WordTableView->currentIndex();
    QString word = currIndex.data().toString();
    if(speakMgr != NULL)
    {
        speakMgr->deleteLater();
        speakMgr = NULL;
    }
    speakMgr = new SpeakMgr(speakConfig,this);
    connect(speakMgr,SIGNAL(SpeakFininshed()),this,SLOT(setButtonState()));
    speakMgr->Speak(word,500,1);
}

void DictMainWindow::setButtonState()
{
    ui->action_Speak->setEnabled(true);
    if(speakMgr != NULL)
    {
        speakMgr->deleteLater();
        speakMgr = NULL;
    }
}

void DictMainWindow::on_ExpComboBox_currentIndexChanged(int index)
{
    ui->WordLineEdit->setFocus();
    ui->MeanTextBrowser->clear();
    ui->action_Speak->setEnabled(false);
    ui->action_AddToNewWord->setEnabled(false);

    if(index == 0)
    {
        model->setFilter(QString("Wort like '%1%'").arg(ui->WordLineEdit->text()));
        //显示结果
        model->select();
    }
    else if(index == 1)
    {
        model->setFilter(QString("Wort like '%%1%'").arg(ui->WordLineEdit->text()));
        //显示结果
        model->select();
    }
    else if(index == 2)
    {
        model->setFilter(QString("Wort like '%%1'").arg(ui->WordLineEdit->text()));
        //显示结果
        model->select();
    }
}
