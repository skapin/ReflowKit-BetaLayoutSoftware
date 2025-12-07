#include <QTranslator>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    if (translator.load(QLocale(), "ReflowKitController", "_", ":/")) {
        QCoreApplication::installTranslator(&translator);
    }

    MainWindow w;
    w.show();
    
    return a.exec();
}
