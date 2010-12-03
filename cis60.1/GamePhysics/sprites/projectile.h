#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QLinearGradient>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QPen>
#include <QGradient>
#include <QColor>
#include <QVector2D>
#include <QDebug>
#include <QGraphicsScene>
#include <math.h>
#include <sprites/fixedrectangle.h>
#include <sprites/stackablesphere.h>

#define GRAVITY -4.5

class Projectile : public QGraphicsEllipseItem
{
private:
    int x, y, angle, velocity;
    int lastX, lastY;
    double mass;
    double horizontalVelocity,verticalVelocity;
    QVector2D position, pVelocity, acceleration, initialVelocity;
public:
    Projectile(int x, int y, int angle, int velocity);
    void updatePosition();
    void handleCollision(QGraphicsItem *obstacle);
    void handleCollision(FixedRectangle *obstacle);
    void handleCollision(StackableSphere *obstacle);
    void resolveCollisionType(QGraphicsItem *ob);
    double getImpactAngle();
    void setMass(double m);
    double getMass();
    QVector2D getVelocity();
    QVector2D getInitialVelocity();
    QVector2D getPosition();
    void setVelocity(QVector2D v);
};

#endif // PROJECTILE_H
