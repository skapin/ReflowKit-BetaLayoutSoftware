#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>

#include "graphicaltemp.h"
#include "reflowcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_refreshTime_valueChanged(int arg1);
    void refreshTempGraph();

    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;

    QTimer _tempGraphTimer;
    GraphicalTemp* _graphTemp;
    ReflowController _reflowC;
};

#endif // MAINWINDOW_H
