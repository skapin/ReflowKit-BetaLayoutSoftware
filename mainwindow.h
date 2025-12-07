#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QFileDialog>
#include <qwt_plot.h>
#include <chrono>

#include "reflowcontroller.h"
/**
 * @author Florian Boudinet
 * @since May 2013
 *
 * florian.boudinet@gmail.com
 * fboudinet.frenchdev.com
 * GitHub : SkapiN
 *
 * Schema :
 *
 *              RS232
 *                |
 *               Uart
 *                |
 *        ReflowController--------GraphTemp
 *                |                   |
 *            MainWindow---------------
 *
 *
 *
 * BaudRate 9600
 * Device used : ReflowKit BetaLayout.
 *
 * Works fine on Linux 32/64Bit, ( Ubuntu 12.x and Debian (Wheezy) ).
 **/


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
    void updateUiComponents();
    void on_refreshTime_valueChanged(int arg1);
    void refreshTempGraph();

    void on_clearButton_clicked();
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
    void on_refreshTimeUi_valueChanged(int arg1);

    void on_connectButton_clicked();

    void on_consoleCommand_returnPressed();

    void on_learnButton_clicked();

    void on_tempoffset_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_forceUpdate_clicked();

    void on_pushButton_2_clicked();

    void on_editButton_clicked();

private:
    Ui::MainWindow *ui;

    QTimer _refreshReflowControllerTimer;
    QTimer _tempGraphTimer;
    QTimer _uiRefreshTimer;
    ReflowController _reflowC;
    bool _canEditValue;
    void setEditValue( bool enable );

};

#endif // MAINWINDOW_H

