#ifndef STACKABLESPHERE_H
#define STACKABLESPHERE_H

#include <QGraphicsEllipseItem>
#include <QVector2D>
#include <QLinearGradient>
#include <QBrush>
#include <QPen>

class StackableSphere : public QGraphicsEllipseItem
{
private:
    int x, y, lastX, lastY;
    double mass;
    QVector2D velocity, position;
public:
    StackableSphere();
    void setMass(double m);
    double getMass();
    void setVelocity(QVector2D v);
    QVector2D getVelocity();
};

#endif // STACKABLESPHERE_H
