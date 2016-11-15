#ifndef DELETEDICTDIALOG_H
#define DELETEDICTDIALOG_H

#include <QDialog>
#include "MyDictList.h"

namespace Ui {
class DeleteDictDialog;
}

class DeleteDictDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DeleteDictDialog(MyDictList * dictlistDB, QWidget *parent = 0);
    ~DeleteDictDialog();
    
private slots:
    void on_DictTableWidget_customContextMenuRequested(const QPoint &pos);

    void on_action_Delete_triggered();

    void on_AcceptButton_clicked();

protected:
    void showDictList();

private:
    Ui::DeleteDictDialog *ui;
    MyDictList *dictListDB;
};

#endif // DELETEDICTDIALOG_H
