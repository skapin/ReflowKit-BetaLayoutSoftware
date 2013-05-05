#ifndef GRAPHTEMP_H
#define GRAPHTEMP_H
/**
 * Classs using Qwt(based on QWidget).
 * Display a grah about reflowkit temperature.
 *
 **/
#include <QWidget>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>

class GraphTemp : public QwtPlot
{
    Q_OBJECT
public:
    explicit GraphTemp(QWidget *parent = 0);
    
signals:
    
public slots:
private:
    QwtPlotGrid _grid;
    QwtPlotCurve _tempCurve;
    
};

#endif // GRAPHTEMP_H
