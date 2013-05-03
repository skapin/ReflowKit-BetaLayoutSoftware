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

    void on_pushButton_clicked();

    void on_phttemp_valueChanged(int arg1);

    void on_phttime_valueChanged(int arg1);

    void on_phtpwr_valueChanged(int arg1);

    void on_soaktemp_valueChanged(int arg1);

    void on_soaktime_valueChanged(int arg1);

    void on_soakpwr_valueChanged(int arg1);

    void on_reflowtemp_valueChanged(int arg1);

    void on_reflowtime_valueChanged(int arg1);

    void on_reflowpwr_valueChanged(int arg1);

    void on_dwelltemp_valueChanged(int arg1);

    void on_dwelltime_valueChanged(int arg1);

    void on_dwellpwr_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QTimer _tempGraphTimer;
    GraphicalTemp* _graphTemp;
    ReflowController _reflowC;
};

#endif // MAINWINDOW_H
