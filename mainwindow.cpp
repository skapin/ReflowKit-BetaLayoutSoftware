#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _graphTemp = new GraphicalTemp(400,400,this);
    _graphTemp->setGeometry(50,50,400,400);
    _tempGraphTimer.start( ui->refreshTime->value() );
    connect( &_tempGraphTimer, SIGNAL(timeout()), this, SLOT(refreshTempGraph()) );
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

void MainWindow::refreshTempGraph()
{
    ui->temp->setText( QString::number(_reflowC.getCurrentTemp()) );

}

void MainWindow::on_clearButton_clicked()
{
    ui->consoleOutput->clear();
}

void MainWindow::on_pushButton_clicked()
{
    if ( _reflowC._deviceOpen ) {
        _reflowC.closeDevice();
        ui->connectButton->setText("Deconnected");
    }
    else {
        if ( _reflowC.openDevice( ui->pathToDevice->text().toStdString() ) )
            ui->connectButton->setText("Connected");
    }

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
