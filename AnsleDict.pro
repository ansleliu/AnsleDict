#-------------------------------------------------
#
# Project created by QtCreator 2014-05-05T10:17:22
#
#-------------------------------------------------

QT       += core gui sql phonon network webkit

TARGET = AnsleDict
TEMPLATE = app


SOURCES += main.cpp\
        DictMainWindow.cpp \
    MySQLite.cpp \
    PathMgr.cpp \
    MyDictList.cpp \
    AddDictDialog.cpp \
    DeleteDictDialog.cpp \
    ConfigDialog.cpp \
    CreatWordListDB.cpp \
    AboutDialog.cpp \
    SpeakTTS.cpp \
    SpeakMgr.cpp \
    SpeakGoogle.cpp \
    DownloadControl/DownloadControl.cpp \
    DownloadControl/Download.cpp \
    MyLineEdit.cpp \
    UserSelectDialog.cpp \
    UserMgr.cpp \
    ConfigFile.cpp \
    QtSpeech.cpp

HEADERS  += DictMainWindow.h \
    MySQLite.h \
    PathMgr.h \
    MyDictList.h \
    AddDictDialog.h \
    DeleteDictDialog.h \
    ConfigDialog.h \
    CreatWordListDB.h \
    AboutDialog.h \
    Thread/thread.h \
    SpeakTTS.h \
    SpeakMgr.h \
    SpeakGoogle.h \
    eSpeak/speak_lib.h \
    DownloadControl/DownloadControl.h \
    DownloadControl/Download.h \
    MyLineEdit.h \
    UserSelectDialog.h \
    UserMgr.h \
    ConfigFile.h \
    QtSpeech.h

FORMS    += DictMainWindow.ui \
    AddDictDialog.ui \
    DeleteDictDialog.ui \
    ConfigDialog.ui \
    AboutDialog.ui \
    UserSelectDialog.ui

UI_DIR = ./ui
MOC_DIR = TEMP/moc
RCC_DIR = TEMP/rcc
OBJECTS_DIR = TEMP/obj

RESOURCES += \
    rc.qrc

RC_FILE = MyApp.rc
OTHER_FILES += \
    MyApp.rc

win32: LIBS += -L$$PWD/eSpeak/ -lespeak_lib

INCLUDEPATH += $$PWD/eSpeak
DEPENDPATH += $$PWD/eSpeak
