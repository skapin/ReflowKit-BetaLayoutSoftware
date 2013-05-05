#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T12:19:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReflowKitController
TEMPLATE = app

CONFIG += qwt
INCLUDEPATH += /usr/local/qwt-6.0.3-svn/include
LIBS += -L/usr/local/qwt-6.0.3-svn/lib -lqwt

SOURCES += main.cpp\
        mainwindow.cpp\
    uart.cpp \
    reflowcontroller.cpp \
    graphtemp.cpp

HEADERS  += mainwindow.h\
    uart.h \
    reflowcontroller.h \
    graphtemp.h

FORMS    += mainwindow.ui
