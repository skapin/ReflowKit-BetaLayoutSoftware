#include "graphtemp.h"

GraphTemp::GraphTemp(QWidget *parent) :
    QwtPlot(parent)
{
    setCanvasBackground(Qt::white);

    _grid.attach( this );
    _tempCurve.attach( this );
    replot();
}
