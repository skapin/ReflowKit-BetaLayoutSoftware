#include "graphtemp.h"


GraphTemp::GraphTemp(QWidget *parent) :
    QwtPlot(parent)
{
    setCanvasBackground(Qt::white);
    _currentTime = 0.0;
    _startTime = 0.0;
    _grid.attach( this );
    _tempCurve.attach( this );


    _legend.setFrameStyle(QFrame::Box|QFrame::Sunken);
    this->insertLegend(&_legend, QwtPlot::BottomLegend);
    // Define the QPEn for the curve
    QPen pen;
    pen.setWidth(3);
    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    _tempCurve.setPen( pen );
    _tempCurve.setTitle( "currentTemp" );

    // Fixe the X/Y axis scale
    this->setAxisScale(QwtPlot::yLeft,0.0,300.0,25.0);
    replot();
}

void GraphTemp::setLine(QwtPlotCurve *curve, int value, QPen pen, string legendName) {
    double x[2]= {_startTime, _currentTime};
    double y[2] ={0.0,0.0};
    y[0] = y[1] = value;

    curve->setSamples( x,y ,2 );

    curve->setPen( pen );
    curve->setTitle( (legendName+" "+(QString::number(value)).toStdString()).c_str() );
    curve->attach( this );

}

void GraphTemp::setReflowCurve(int value) {
    setLine( &_reflowCurve, value, QPen(Qt::blue,3, Qt::DashLine), "Reflow" );
}

void GraphTemp::setPhtCurve(int value) {
    setLine( &_phtCurve, value, QPen(Qt::darkYellow,3, Qt::DashDotLine), "Pht" );
}

void GraphTemp::setSoakCurve(int value) {
    setLine( &_soakCurve, value, QPen(Qt::red,3, Qt::DashDotDotLine), "Soak" );
}


void GraphTemp::setDWellCurve(int value) {
    setLine( &_dwellCurve, value, QPen(Qt::darkCyan,3, Qt::DotLine), "Dwell" );
}


void GraphTemp::setTempCurve( QVector<double>* temps, QVector<double>* times ) {
    if ( temps == NULL || times == NULL )
        return;
    if ( times->empty() || temps->empty() )
        return;
    _currentTime = times->last();
    _startTime = times->first();
    _tempCurve.setSamples( times->data(), temps->data(), temps->size() );
    replot();
}
