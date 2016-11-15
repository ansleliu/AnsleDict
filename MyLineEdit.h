#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void focusInEvent ( QFocusEvent * e );
    void mouseDoubleClickEvent ( QMouseEvent * e );
};

#endif // MYLINEEDIT_H
