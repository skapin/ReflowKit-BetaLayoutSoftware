#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T12:19:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReflowKitController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
uart.cpp \
    graphicaltemp.cpp \
    reflowcontroller.cpp

HEADERS  += mainwindow.h\
uart.h \
    graphicaltemp.h \
    reflowcontroller.h

FORMS    += mainwindow.ui
