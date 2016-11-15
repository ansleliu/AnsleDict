#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void MyLineEdit::focusInEvent(QFocusEvent *e)
{
    Q_UNUSED(e);
//    this->selectAll();
}

void MyLineEdit::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
//    this->selectAll();
}
