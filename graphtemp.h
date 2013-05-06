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
#include <qwt_legend.h>
#include <QVector>
#include <QPen>
#include <string>

using namespace std;

class GraphTemp : public QwtPlot
{
    Q_OBJECT
public:
    explicit GraphTemp( QWidget *parent = 0 );
    void addTemp( int temp );
    void setReflowCurve(int value);
    void setSoakCurve(int value);
    void setDWellCurve(int value);
    void setPhtCurve(int value);
    void setLine(QwtPlotCurve* curve, int value, QPen pen, string legendName);
    
signals:
    
public slots:
private:
    QwtPlotGrid _grid;
    QwtLegend _legend;
    QwtPlotCurve _tempCurve;
    QwtPlotCurve _phtCurve;
    QwtPlotCurve _reflowCurve;
    QwtPlotCurve _soakCurve;
    QwtPlotCurve _dwellCurve;

    QVector<double> _temps;
    QVector<double> _times;
    static int MAX_SIZE_TEMP_LIST;
    int _cmpTemp;
};

#endif // GRAPHTEMP_H
