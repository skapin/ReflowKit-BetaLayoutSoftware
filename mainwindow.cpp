#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); // setup the UI

    updateUiComponents();//Update UI component value, based on ReflowController Value.

    /*_graphTemp = new GraphicalTemp(400,400,this);
    _graphTemp->setGeometry(50,50,400,400);*/

    _tempGraphTimer.start( ui->refreshTime->value()*1000 );
    connect( &_tempGraphTimer, SIGNAL(timeout()), this, SLOT(refreshTempGraph()) );

    // Update UI compoenent timer.
    _uiRefreshTimer.start( ui->refreshTimeUi->value()*1000);
    connect( &_uiRefreshTimer, SIGNAL(timeout()), this, SLOT(updateUiComponents()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refreshTime_valueChanged(int arg1)
{
    _tempGraphTimer.setInterval( arg1 );
    _reflowC.setTempShow( arg1 );

}
void MainWindow::updateUiComponents() {
    _reflowC.parseUart();
    ui->phttemp->setValue( _reflowC.getPhtTemp() );
    ui->phttime->setValue( _reflowC.getPhtTime() );
    ui->phtpwr->setValue( _reflowC.getPhtPwr() );

    ui->reflowtemp->setValue( _reflowC.getReflowTemp() );
    ui->reflowtime->setValue( _reflowC.getReflowTime() );
    ui->reflowpwr->setValue( _reflowC.getReflowPwr() );

    ui->soaktemp->setValue( _reflowC.getSoakTemp() );
    ui->soaktime->setValue( _reflowC.getSoakTime() );
    ui->soakpwr->setValue( _reflowC.getSoakPwr() );

    ui->dwelltemp->setValue( _reflowC.getDwellTemp() );
    ui->dwelltime->setValue( _reflowC.getDwellTime() );
    ui->dwellpwr->setValue( _reflowC.getDwellPwr() );

    QStringList* list = _reflowC.getDatas();
    QString s;
    QString s_all;
    foreach( s, *list )
        s_all = s +s_all;
    ui->consoleOutput->setText( s_all );
}


void MainWindow::on_connectButton_clicked()
{
    if ( _reflowC.getUartDevice()->isDeviceOpen() ) {
        _reflowC.closeDevice();
        ui->connectButton->setText("Deconnected");
        ui->statusBar->showMessage("The device is disconnected.");
    }
    else {
        ui->statusBar->showMessage("Trying a connection to the device...");
        if ( _reflowC.openDevice( ui->pathToDevice->text().toStdString() ) )
        {
            ui->connectButton->setText("Connected");
            ui->statusBar->showMessage("Device connected.");
        }
        else
            ui->statusBar->showMessage("Can't connect to the device...");
    }


}

void MainWindow::on_consoleCommand_returnPressed()
{
    if ( ui->consoleCommand->text() != "" )
    {
        _reflowC.getUartDevice()->send( ui->consoleCommand->text().toStdString() );
        ui->statusBar->showMessage( "Sendind command from console inpute : "+ui->consoleCommand->text() );
    }
    else
        ui->statusBar->showMessage( "" );
}


//***************************** SET**************************

void MainWindow::refreshTempGraph()
{
    ui->temp->setText( QString::number(_reflowC.getCurrentTemp()) );

}

void MainWindow::on_clearButton_clicked()
{
    ui->consoleOutput->clear();
}

void MainWindow::on_phttemp_valueChanged(int arg1)
{
    _reflowC.setPhtTemp( arg1 );
}

void MainWindow::on_phttime_valueChanged(int arg1)
{
    _reflowC.setPhtTime( arg1 );
}

void MainWindow::on_phtpwr_valueChanged(int arg1)
{
    _reflowC.setPhtPwr( arg1 );
}

void MainWindow::on_soaktemp_valueChanged(int arg1)
{
    _reflowC.setSoakTemp( arg1 );
}

void MainWindow::on_soaktime_valueChanged(int arg1)
{
    _reflowC.setSoakTime( arg1 );
}

void MainWindow::on_soakpwr_valueChanged(int arg1)
{
    _reflowC.setSoakPwr( arg1 );
}

void MainWindow::on_reflowtemp_valueChanged(int arg1)
{
    _reflowC.setReflowTemp( arg1 );
}

void MainWindow::on_reflowtime_valueChanged(int arg1)
{
    _reflowC.setReflowTime( arg1 );
}

void MainWindow::on_reflowpwr_valueChanged(int arg1)
{
    _reflowC.setReflowPwr( arg1 );
}

void MainWindow::on_dwelltemp_valueChanged(int arg1)
{
    _reflowC.setDwellTemp( arg1 );
}

void MainWindow::on_dwelltime_valueChanged(int arg1)
{
    _reflowC.setDwellTime( arg1 );
}

void MainWindow::on_dwellpwr_valueChanged(int arg1)
{
    _reflowC.setDwellPwr( arg1 );
}

void MainWindow::on_refreshTimeUi_valueChanged(int arg1)
{
    _uiRefreshTimer.setInterval( arg1 );
}
