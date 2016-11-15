#include "AddDictDialog.h"
#include "ui_AddDictDialog.h"
#include "QFileInfo"
#include "QFileDialog"
#include "PathMgr.h"
#include "QMessageBox"

AddDictDialog::AddDictDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDictDialog)
{
    ui->setupUi(this);
    ui->OKButton->setEnabled(false);
}

AddDictDialog::~AddDictDialog()
{
    delete ui;
}

void AddDictDialog::on_OKButton_clicked()
{
    accept();
}

void AddDictDialog::on_QuitButton_clicked()
{
    reject();
}

void AddDictDialog::on_ImportButton_clicked()
{
    dictPath = PathManage::makePathStr("/AnsleDict/MyDict/Dict/");
    QString filename = QFileDialog::getOpenFileName(this,
            tr("添加新词典"), dictPath, tr("数据库文件(*.db)"));
    if (filename.isEmpty())
        return;
    else if(!filename.contains(".db", Qt::CaseInsensitive))
    {
        QMessageBox::warning(this, tr("出错了"),
         (QString("请把词典文件放到%1目录下并将其打开！").arg(dictPath)));
        return;
    }
    else
    {
        QFileInfo fd(filename);
        dictName = fd.baseName();
        dictPath = fd.filePath();
        ui->DictNameLineEdit->setText(dictName);
        ui->DictPathLineEdit->setText(dictPath);
        ui->OKButton->setEnabled(true);
    }
}

QString AddDictDialog::getDictName()
{
    return ui->DictNameLineEdit->text();
}

QString AddDictDialog::getDictPath()
{
    return dictPath;
}
