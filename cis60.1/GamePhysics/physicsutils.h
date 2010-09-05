#ifndef PHYSICSUTILS_H
#define PHYSICSUTILS_H

#include <QtGui/QGraphicsRectItem>

class PhysicsUtils
{
    public:
       static bool objectsCollide(QRectF p, QRectF o);

    private:
        PhysicsUtils(){}
};

#endif // PHYSICSUTILS_H
