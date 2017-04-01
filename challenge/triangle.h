#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QQuickPaintedItem>

class Triangle : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Triangle(QQuickItem* parent=0);
    virtual void paint(QPainter *painter);

signals:

public slots:

};

#endif // TRIANGLE_H
