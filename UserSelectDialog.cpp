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
    //��ʼ��ComboBox�е��û��б�
    initComboBoxUserList();

    // ��������¼���û�
    defaultUser = userMgr->getDefaultUser();
    int index = ui->UserListComboBox->findText(defaultUser);
    if (-1 != index)//�û�����
    {
        ui->UserListComboBox->setCurrentIndex(index);
        on_UserListComboBox_currentIndexChanged(defaultUser);
        // �����Զ���¼��ť
        bool bAutoSelect = userMgr->getAutoSelect();
        ui->RemeberCheckBox->setCheckState(bAutoSelect ? Qt::Checked : Qt::Unchecked);
        //�����Զ���¼ѡ��
        on_RemeberCheckBox_clicked(bAutoSelect);

        if (bAutoSelect && !m_bDisableAutoSelect)
        {
            //����Զ���¼��һ��ʱ����Զ���¼
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
    //��ȡ�û���Ϣ
    QStringList userList = userMgr->getUserList();
    //�����ñ�
    QStringListIterator Iterator(userList);
    //��combobox������û�
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
    //��¼Ĭ���û�
    userMgr->setDefaultUser(userName);
    userMgr->setAutoSelect(ui->RemeberCheckBox->checkState());

    QDialog::accept();
}

void UserSelectDialog::on_QuitButton_clicked()
{
//    if (QMessageBox::information(this, tr("��ʾ��Ϣ"), tr("��ȷ��Ҫ�˳���?"),
//                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
//    {
        QDialog::reject();
//    }
}
