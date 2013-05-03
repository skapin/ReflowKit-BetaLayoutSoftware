#include "graphicaltemp.h"

GraphicalTemp::GraphicalTemp(QWidget *parent) :
    QWidget(parent)
{
}

GraphicalTemp::GraphicalTemp(int width, int height, QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(width, height);
}

void GraphicalTemp::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setBackground(QBrush(Qt::white));

    QRectF rectangle(0.0, 0.0, 600.0, 600.0);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    painter.drawArc(rectangle, startAngle, spanAngle);

}
