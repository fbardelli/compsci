#ifndef PHYSICSUTILS_H
#define PHYSICSUTILS_H

#include <QtGui/QGraphicsRectItem>
#include "gameConstants.h"

class PhysicsUtils
{
    public:
       static bool objectsCollide(QRectF p, QRectF o);
       static void moveToEdge(QRectF &p, QRectF o, Direction dir);

    private:
        PhysicsUtils(){}
};

#endif // PHYSICSUTILS_H
