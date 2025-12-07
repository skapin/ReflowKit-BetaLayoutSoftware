#include "graphtemp.h"


GraphTemp::GraphTemp(QWidget *parent) :
    QwtPlot(parent)
{
    setCanvasBackground(Qt::white);
    _currentTime = 0.0;
    _startTime = 0.0;
    _grid.enableX( false );
    _grid.setPen( QPen(Qt::gray, 1));
    _grid.attach( this );
    _tempCurve.attach( this );


    _legend.setFrameStyle(QFrame::Box|QFrame::Sunken);
    this->insertLegend(&_legend, QwtPlot::BottomLegend);

    // define the QPen for each Curve
    _reflowCurve.setPen( QPen(Qt::darkGreen,2, Qt::DashLine) );
    _phtCurve.setPen( QPen(Qt::darkYellow,2, Qt::DashDotLine) );
    _soakCurve.setPen( QPen(Qt::red,2, Qt::DashDotDotLine) );
    _dwellCurve.setPen( QPen(Qt::darkCyan,2, Qt::DotLine) );
    _timesFrameOffset = 0;

    QPen pen;
    pen.setWidth(3);
    pen.setBrush(Qt::darkCyan);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    _tempCurve.setPen( pen );

    // Define the brush ( color under the curve)
    QColor tempcolor( Qt::darkCyan );
    tempcolor.setAlpha( 40 );
    _tempCurve.setTitle( tr("Temperature") );
    _tempCurve.setBrush( tempcolor );

    // Fixe the X/Y axis scale
    this->setAxisScale(QwtPlot::yLeft,0.0,300.0,25.0);

    replot();
}

void GraphTemp::setTimeFrameOfset(int offset) {
    _timesFrameOffset = offset;
}

void GraphTemp::resetGraph() {
    double x[1]= {0};
    double y[1] ={0};
    _tempCurve.setSamples( x, y, 0 );
}

void GraphTemp::setLine(QwtPlotCurve *curve, int value, string legendName) {
    double x[2]= {_startTime+_timesFrameOffset, _currentTime};
    double y[2] ={0.0,0.0};
    y[0] = y[1] = value;

    curve->setSamples( x,y ,2 );

    curve->setTitle( (legendName+" "+(QString::number(value)).toStdString()).c_str() );
    curve->attach( this );

}

void GraphTemp::setReflowCurve(int value) {
    setLine( &_reflowCurve, value, "Reflow" );
}

void GraphTemp::setPhtCurve(int value) {
    setLine( &_phtCurve, value, "Pht" );
}

void GraphTemp::setSoakCurve(int value) {
    setLine( &_soakCurve, value, "Soak" );
}


void GraphTemp::setDWellCurve(int value) {
    setLine( &_dwellCurve, value, "Dwell" );
}


void GraphTemp::setTempCurve( QVector<double>* temps, QVector<double>* times ) {
    if ( temps == NULL || times == NULL )
        return;
    if ( times->empty() || temps->empty() )
        return;
    if ( times->size() <= 1)
        return;

    _currentTime = times->last();
    _startTime = times->first();
    //if new timer, cause reflow start or something, we need to reset the graph to prevent false output curves
    if ( _currentTime < _startTime )
        resetGraph();

    double* x = times->data();
    double* y = temps->data();
    _tempCurve.setSamples( &(x[_timesFrameOffset]), &(y[_timesFrameOffset]), temps->size() -_timesFrameOffset );
    replot();
}
