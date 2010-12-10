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
#include <math.h>
#include <QGraphicsScene>
#include <sprites/fixedrectangle.h>
#include <sprites/stackablesphere.h>
#include <physicsutils.h>

#define GRAVITY -4.5

class Projectile : public QGraphicsEllipseItem
{
private:
    int x, y, angle, velocity;
    double mass;
    double horizontalVelocity,verticalVelocity;
    QVector2D position, lastPosition, pVelocity, acceleration, initialVelocity;
public:
    Projectile(int x, int y, int angle, int velocity);
    void updatePosition();
    void handleCollision(QGraphicsItem *obstacle);
    void handleCollision(FixedRectangle *obstacle);
    void handleCollision(StackableSphere *obstacle);
    void resolveCollisionType(QGraphicsItem *ob);
    //double getImpactAngle();
    void setMass(double m);
    double getMass();
    QVector2D getVelocity();
    void setVelocity(QVector2D v);
    QVector2D getInitialVelocity();
    QVector2D getAcceleration();
    void setAcceleration(QVector2D a);
    QVector2D getPosition();
    void setPosition(QVector2D p);
    // Enable the use of qgraphicsitem_cast with this item.
    enum { Type = UserType + 2 };
    int type() const {return Type;};
};

#endif // PROJECTILE_H
