#-------------------------------------------------
#
# Project created by QtCreator 2018-03-23T12:37:03
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    dstatistics.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    dstatistics.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dstatistics.ui
