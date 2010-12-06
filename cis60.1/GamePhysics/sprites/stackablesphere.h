#ifndef STACKABLESPHERE_H
#define STACKABLESPHERE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QVector2D>
#include <QLinearGradient>
#include <QPainterPath>
#include <QBrush>
#include <QPen>
#include "physicsutils.h"

class StackableSphere : public QGraphicsEllipseItem
{
private:
    int x, y, lastX, lastY, id;
    double mass;
    bool collisionState;
    QVector2D velocity, position, acceleration;
public:
    StackableSphere();
    void setMass(double m);
    double getMass();
    void setID(int i);
    int getID();
    void setVelocity(QVector2D v);
    QVector2D getVelocity();
    void updatePosition();
    void setPosition(QVector2D p);
    QVector2D getPosition();
    void setAcceleration(QVector2D a);
    QVector2D getAcceleration();
    void applyGravity();
    void setCollisionState(bool s);
};

#endif // STACKABLESPHERE_H
