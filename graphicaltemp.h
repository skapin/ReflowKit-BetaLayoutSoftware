#ifndef GRAPHICALTEMP_H
#define GRAPHICALTEMP_H

#include <QWidget>
#include <QPainter>

class GraphicalTemp : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicalTemp(QWidget *parent = 0);
    GraphicalTemp(int width, int height, QWidget *parent);
    
signals:
    
public slots:
private:
    void paintEvent(QPaintEvent *);
    
};

#endif // GRAPHICALTEMP_H
