#include "DeleteDictDialog.h"
#include "ui_DeleteDictDialog.h"
#include "QTableWidgetItem"
#include "QMessageBox"
#include "QAction"
#include "QMenu"

DeleteDictDialog::DeleteDictDialog(MyDictList *dictlistDB, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDictDialog)
{
    ui->setupUi(this);
    dictListDB = dictlistDB;

    showDictList();
}

DeleteDictDialog::~DeleteDictDialog()
{
    delete ui;
    dictListDB = NULL;
}

void DeleteDictDialog::on_DictTableWidget_customContextMenuRequested(const QPoint &pos)
{
    QTableWidgetItem *currentItem = ui->DictTableWidget->itemAt(pos);
    //这种情况是右键的位置不在tableItem的范围内，即在空白位置右击
    if(currentItem == NULL)
    {

    }
    else
    {
        QMenu *popMenu =new QMenu(this);//定义一个右键弹出菜单
        popMenu->addAction(ui->action_Delete);

        popMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置

        delete popMenu;
        popMenu = NULL;
    }
}

void DeleteDictDialog::on_action_Delete_triggered()
{
    QTableWidgetItem *currTabletItem = ui->DictTableWidget->currentItem();
    if(currTabletItem != NULL)
    {
        int row = currTabletItem->row();
        QTableWidgetItem *pathItem = ui->DictTableWidget->item(row,1);
        QString dictPath = pathItem->text();

        if (QMessageBox::information(this, "提示信息", "您确定要删除该词典吗?",
                                     QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            dictListDB->deleteDict(dictPath);
        }
        else
        {

        }

        showDictList();
    }
}

void DeleteDictDialog::showDictList()
{
    ui->DictTableWidget->clear();

    ui->DictTableWidget->setColumnCount(2);
    QStringList headers;
    headers<<"词典名"<<"词典路径";
    ui->DictTableWidget->setHorizontalHeaderLabels(headers);

    QStringList dictNames = dictListDB->getDictNames();
    QStringList dictPaths = dictListDB->getDictPaths();

    ui->DictTableWidget->setRowCount(dictNames.size());

    for(int i=0; i<dictNames.size(); i++)
    {
        ui->DictTableWidget->setItem(i,0,new QTableWidgetItem(dictNames.at(i)));
        ui->DictTableWidget->setItem(i,1,new QTableWidgetItem(dictPaths.at(i)));
    }
}

void DeleteDictDialog::on_AcceptButton_clicked()
{
    accept();
}
