#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QLinearGradient>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QPen>
#include <QGradient>
#include <QDebug>
#include <math.h>
#include <sprites/fixedrectangle.h>

#define GRAVITY -4.5

class Projectile : public QGraphicsEllipseItem
{
private:
    int x, y, angle, velocity, time;
    int lastX, lastY;
    double horizontalVelocity, verticalVelocity;
public:
    Projectile(int x, int y, int angle, int velocity);
    void updatePosition();
    void handleCollision(QGraphicsItem *obstacle);
    void handleCollision(FixedRectangle *obstacle);
};

#endif // PROJECTILE_H
