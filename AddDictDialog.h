#ifndef ADDDICTDIALOG_H
#define ADDDICTDIALOG_H

#include <QDialog>

namespace Ui {
class AddDictDialog;
}

class AddDictDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddDictDialog(QWidget *parent = 0);
    ~AddDictDialog();
    
private slots:
    void on_OKButton_clicked();

    void on_QuitButton_clicked();

    void on_ImportButton_clicked();

public:
    QString getDictName();
    QString getDictPath();

private:
    Ui::AddDictDialog *ui;
    QString dictName;
    QString dictPath;
};

#endif // ADDDICTDIALOG_H
