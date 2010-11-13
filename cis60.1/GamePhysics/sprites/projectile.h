#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QLinearGradient>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QPen>
#include <QGradient>
#include <math.h>

#define GRAVITY -4.5

class Projectile : public QGraphicsEllipseItem
{
private:
    int x, y, angle, velocity, time;
    double horizontalVelocity, verticalVelocity;
public:
    Projectile(int x, int y, int angle, int velocity);
    void updatePosition();
    void deflect();
};

#endif // PROJECTILE_H
