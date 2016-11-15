#include <QtGui/QApplication>
#include "DictMainWindow.h"
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::addLibraryPath("./plugins");

    QTextCodec *codec = QTextCodec::codecForName("System");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    DictMainWindow w;
    w.show();
    
    return a.exec();
}
