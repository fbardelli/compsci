#include "physicsutils.h"

bool PhysicsUtils::objectsCollide(QRectF p, QRectF o){
    int pLeft = p.x();
    int oLeft = o.x();
    int pRight = p.x() + p.width();
    int oRight = o.x() + o.width();
    int pTop   = p.y();
    int oTop   = o.y();
    int pBottom = p.y() + p.height();
    int oBottom = o.y() + o.height();
    // is player fully above obstacle?
    if (pBottom < oTop) return false;
    // is player fully below obstacle?
    if (pTop > oBottom) return false;
    //Is player to the right of obstacle?
    if (pRight < oLeft) return false;
    //Is player to the left of obstacle?
    if (pLeft > oRight) return false;
    //otherwise player collides with obstacle.
    return true;
}
