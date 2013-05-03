#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _graphTemp = new GraphicalTemp(800,800,this);

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


}

void MainWindow::on_clearButton_clicked()
{
    ui->consoleOutput->clear();
}
