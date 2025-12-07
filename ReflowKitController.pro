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
CONFIG += c++2a


unix {
    INCLUDEPATH += /usr/include/qwt/
}
win32 {
    INCLUDEPATH += E:/qwt-6.0/src
}
#LIBS += -L/usr/local/qwt-6.0.3-svn/lib -lqwt

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
RESOURCES += \
    ReflowKitController.qrc
TRANSLATIONS += \
    ReflowKitController_de.ts \
    ReflowKitController_fr.ts