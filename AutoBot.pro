#-------------------------------------------------
#
# Project created by QtCreator 2016-10-11T16:25:05
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoBot
TEMPLATE = app


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/autobot.cpp \
    src/tree/treeitem.cpp \
    src/tree/treemodel.cpp \
    src/mousethread.cpp \
    src/mythread.cpp \
    src/questdialog.cpp \
    src/huffman.cpp \
    src/login.cpp \
    src/compiler.cpp \
    src/findpic.cpp

HEADERS  += header/mainwindow.h \
    header/autobot.h \
    header/tree/treeitem.h \
    header/tree/treemodel.h \
    header/global.h \
    header/mousethread.h \
    header/mythread.h \
    header/questdialog.h \
    header/huffman.h \
    header/login.h \
    header/compiler.h \
    header/findpic.h

FORMS    += mainwindow.ui \
    questdialog.ui \
    login.ui \
    findpic.ui
CONFIG += static

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    autobotico.rc

RC_FILE += \
    autobotico.rc
