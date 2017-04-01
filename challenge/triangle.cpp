#include "triangle.h"
#include <QPainter>

Triangle::Triangle(QQuickItem *parent) : QQuickPaintedItem(parent)
{

}

void Triangle::paint(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::black,5.5));
    QPainterPath p(QPoint(x(),y()));
    p.lineTo(QPoint(x()+width(),y()));
    p.lineTo(QPoint(x()+width()/2.0,y()+height()));
    p.closeSubpath();

    painter->drawPath(p);

    painter->restore();
}
