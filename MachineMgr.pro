#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T17:25:56
#
#-------------------------------------------------

QT       += core gui
QT += sql network

CONFIG += qaxcontainer

TARGET = MachineMgr
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    createwidget.cpp \
    dbcommon.cpp \
    importwidget.cpp \
    querywidget.cpp \
    qexcel.cpp \
    qsingleapplication.cpp \
    waitwidgiet.cpp

HEADERS  += mainwidget.h \
    createwidget.h \
    dbcommon.h \
    importwidget.h \
    querywidget.h \
    qexcel.h \
    qsingleapplication.h \
    waitwidgiet.h

FORMS    += mainwidget.ui \
    createwidget.ui \
    importwidget.ui \
    querywidget.ui \
    waitwidgiet.ui









































