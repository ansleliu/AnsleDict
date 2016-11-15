#include "UserSelectDialog.h"
#include "ui_UserSelectDialog.h"
#include "QMessageBox"
#include "PathMgr.h"
#include "QTimer"

UserSelectDialog::UserSelectDialog(QWidget *parent, bool bDisableAutoSelect) :
    QDialog(parent),m_bDisableAutoSelect(bDisableAutoSelect),
    ui(new Ui::UserSelectDialog)
{
    ui->setupUi(this);

    QString userdbPath = PathManage::makePathStr("/userdata/user.db");

    userMgr = new UserMgr(userdbPath,"UserDB",PathManage::makePathStr("/AnsleDict/MyDict/Config.ini"));
    ////////////////////////////////////////////////////////////////////////////
    //初始化ComboBox中的用户列表
    initComboBoxUserList();

    // 设置最后登录的用户
    defaultUser = userMgr->getDefaultUser();
    int index = ui->UserListComboBox->findText(defaultUser);
    if (-1 != index)//用户存在
    {
        ui->UserListComboBox->setCurrentIndex(index);
        on_UserListComboBox_currentIndexChanged(defaultUser);
        // 处理自动登录按钮
        bool bAutoSelect = userMgr->getAutoSelect();
        ui->RemeberCheckBox->setCheckState(bAutoSelect ? Qt::Checked : Qt::Unchecked);
        //调用自动登录选择
        on_RemeberCheckBox_clicked(bAutoSelect);

        if (bAutoSelect && !m_bDisableAutoSelect)
        {
            //如果自动登录，一段时间后自动登录
            QTimer::singleShot(1500, this, SLOT(on_OKButton_clicked()));
        }
    }
}

UserSelectDialog::~UserSelectDialog()
{
    delete userMgr;
    userMgr = NULL;

    delete ui;
}

void UserSelectDialog::initComboBoxUserList()
{
    ui->UserListComboBox->clear();
    //获取用户信息
    QStringList userList = userMgr->getUserList();
    //遍历该表
    QStringListIterator Iterator(userList);
    //向combobox中添加用户
    while(Iterator.hasNext())
    {
        ui->UserListComboBox->addItem(Iterator.next());
    }
}

void UserSelectDialog::on_RemeberCheckBox_clicked(bool checked)
{
    if (checked)
    {

    }
}

void UserSelectDialog::on_UserListComboBox_currentIndexChanged(const QString &username)
{
    Q_UNUSED(username);
    ui->RemeberCheckBox->setCheckState(Qt::Unchecked);
}

QString UserSelectDialog::getDefaultUser()
{
    return defaultUser;
}

void UserSelectDialog::on_OKButton_clicked()
{
    QString userName = ui->UserListComboBox->currentText();
    defaultUser = userName;
    ///////////////////////////////////////////////////////
    //记录默认用户
    userMgr->setDefaultUser(userName);
    userMgr->setAutoSelect(ui->RemeberCheckBox->checkState());

    QDialog::accept();
}

void UserSelectDialog::on_QuitButton_clicked()
{
//    if (QMessageBox::information(this, tr("提示信息"), tr("您确定要退出吗?"),
//                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
//    {
        QDialog::reject();
//    }
}
