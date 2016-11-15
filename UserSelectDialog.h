#ifndef USERSELECTDIALOG_H
#define USERSELECTDIALOG_H

#include <QDialog>
#include "UserMgr.h"

namespace Ui {
class UserSelectDialog;
}

class UserSelectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit UserSelectDialog(QWidget *parent = 0,bool bDisableAutoSelect = false);
    ~UserSelectDialog();
    
private slots:
    void on_OKButton_clicked();

    void on_QuitButton_clicked();

    void on_RemeberCheckBox_clicked(bool checked);

    void on_UserListComboBox_currentIndexChanged(const QString &username);

public:
    QString getDefaultUser();

private:
    void initComboBoxUserList();

private:
    Ui::UserSelectDialog *ui;
    UserMgr *userMgr;
    bool m_bDisableAutoSelect;
    QString defaultUser;
};

#endif // USERSELECTDIALOG_H
