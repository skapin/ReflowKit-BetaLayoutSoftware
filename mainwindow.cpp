#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); // setup the UI
#ifdef unix
    ui->pathToDevice->setText("/dev/ttyUSB0");
#endif
#ifdef WIN32
    ui->pathToDevice->setText("COM4");
#endif
    setWindowTitle("ReflowKit Controller");
    updateUiComponents();//Update UI component value, based on ReflowController Value.

    setEditValue( false );

    /*_graphTemp = new GraphicalTemp(400,400,this);
    _graphTemp->setGeometry(50,50,400,400);*/

    _tempGraphTimer.start( ui->refreshTime->value()*1000 );
    connect( &_tempGraphTimer, SIGNAL(timeout()), this, SLOT(refreshTempGraph()) );

    // Update UI compoenent timer.
    _uiRefreshTimer.start( ui->refreshTimeUi->value()*1000);
    connect( &_uiRefreshTimer, SIGNAL(timeout()), this, SLOT(updateUiComponents()) );

    // Timer for Reflowcontroller update (ask the showall command i.e updateInformation() )
    _refreshReflowControllerTimer.start(30*1000);// 30 sec
    connect( &_refreshReflowControllerTimer, SIGNAL(timeout()), &_reflowC, SLOT(updateInformation()) );
    ui->frameGraphTempSlider->setMaximum( _reflowC.getTemps()->size()-1 ); // maximum of data stored, i.e max of data show :)

    connect( ui->frameGraphTempSlider, SIGNAL(valueChanged(int)),  ui->graphTemp, SLOT(setTimeFrameOfset(int)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setEditValue(bool enable) {
    _canEditValue = enable;

    ui->phttemp->setReadOnly( !enable );
    ui->phttime->setReadOnly( !enable );
    ui->phtpwr->setReadOnly( !enable );

    ui->reflowtemp->setReadOnly( !enable );
    ui->reflowtime->setReadOnly( !enable );
    ui->reflowpwr->setReadOnly( !enable );

    ui->soaktemp->setReadOnly( !enable );
    ui->soaktime->setReadOnly( !enable );
    ui->soakpwr->setReadOnly( !enable );

    ui->dwelltemp->setReadOnly( !enable );
    ui->dwelltime->setReadOnly( !enable );
    ui->dwellpwr->setReadOnly( !enable );
    ui->tempoffset->setReadOnly( !enable );
    if ( enable ) {
        ui->editButton->setText("Update valeurs");
    }
    else {
        ui->editButton->setText("Editer");
    }

}

void MainWindow::on_refreshTime_valueChanged(int arg1)
{
    _tempGraphTimer.setInterval( arg1*1000 );
    _reflowC.setTempShow( arg1 );

}
void MainWindow::updateUiComponents() {
    _reflowC.checkUartDataReady();

    ui->frameGraphTempSlider->setMaximum( _reflowC.getTemps()->size()-1 ); // maximum of data stored, i.e max of data show :)

    if ( !_canEditValue ) {
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
        ui->tempoffset->setValue( _reflowC.getTempoffset() );
        ui->stateLabel->setText( _reflowC.state.c_str() );
    }

    QStringList* list = _reflowC.getDatas();
    QString s;
    QString s_all;

    foreach( s, *list ) {
        s_all = s +s_all;
    }
    ui->consoleOutput->setText( s_all );
}


void MainWindow::on_connectButton_clicked()
{
    if ( _reflowC.getUartDevice()->isDeviceOpen() ) {
        _reflowC.closeDevice();
        ui->connectButton->setText("Connect");
        ui->statusBar->showMessage("The device is disconnected.");
    }
    else {
        ui->statusBar->showMessage("Trying a connection to the device...");
        if ( _reflowC.openDevice( ui->pathToDevice->text().toStdString() ) )
        {
            _reflowC.updateInformation();
            ui->connectButton->setText("Disconnect");
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
    if ( ! _reflowC.getUartDevice()->isDeviceOpen() )
        return;
    // always set TempCurve 1st, cause it memorize the start and currentTime
    ui->graphTemp->setTempCurve( _reflowC.getTemps(), _reflowC.getTimes() );
    ui->temp->setText( QString::number(_reflowC.getCurrentTemp()) );
    ui->graphTemp->setReflowCurve( _reflowC.getReflowTemp());
    ui->graphTemp->setSoakCurve( _reflowC.getSoakTemp());
    ui->graphTemp->setDWellCurve( _reflowC.getDwellTemp());
    ui->graphTemp->setPhtCurve( _reflowC.getPhtTemp() );

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
    _uiRefreshTimer.setInterval( arg1*1000 );
}

void MainWindow::on_learnButton_clicked()
{
    _reflowC.startLearning();
}

void MainWindow::on_tempoffset_valueChanged(int arg1)
{
    _reflowC.setTempoffset( arg1 );
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "./log_reflowkit.cvs");
    _reflowC.exportCVS( fileName.toStdString(), ',' );
}

void MainWindow::on_forceUpdate_clicked()
{
    _reflowC.updateInformation();
    this->updateUiComponents();
}

void MainWindow::on_pushButton_2_clicked()
{
    _reflowC.resetTimeTemps();
}

void MainWindow::on_editButton_clicked()
{
    setEditValue( !_canEditValue );
}
