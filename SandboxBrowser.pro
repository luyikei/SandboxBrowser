#-------------------------------------------------
#
# Project created by QtCreator 2014-08-14T13:29:46
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SandboxBrowser
TEMPLATE = app

LIBS += -lseccomp

SOURCES += main.cpp\
        sandboxbrowser.cpp \
    sandboxprocess.cpp

HEADERS  += sandboxbrowser.h \
    sandboxprocess.h

FORMS    += sandboxbrowser.ui
