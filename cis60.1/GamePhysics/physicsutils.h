#ifndef PHYSICSUTILS_H
#define PHYSICSUTILS_H

#include <QtGui/QGraphicsRectItem>
#include "gameConstants.h"
#include <QVector2D>
#include "math.h"
#include <QDebug>

class PhysicsUtils
{
    public:
       static bool objectsCollide(QRectF p, QRectF o);
       static void moveToEdge(QRectF &p, QRectF o, Direction dir);
       static Direction reverseDirection(Direction dir);
       static QVector2D normalVector (QVector2D vector);
       static QVector2D componentVector(QVector2D vector, QVector2D directionVector);
       static double component (QVector2D vector, QVector2D directionVector);
       static double magnitude(QVector2D v);
       static QVector2D resolveFixedCollision(QVector2D obVelocity, QVector2D normal);
    private:
        PhysicsUtils(){}
};

#endif // PHYSICSUTILS_H
