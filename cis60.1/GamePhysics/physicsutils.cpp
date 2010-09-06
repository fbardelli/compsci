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

void PhysicsUtils::moveToEdge(QRectF &p, QRectF o, Direction dir){
    int pHeight = p.height();
    int pWidth = p.width();
    if(dir == Right){
        //qDebug() << "px:" << p.x() << " ox:" << o.x() << " pw:" << p.width() << " ow:" << o.width();
        p.moveTo( (o.x()-pWidth-1),p.y());
    }else if (dir == Left){
        p.moveTo(o.x()+pWidth+1,p.y());
    }else if (dir == Down){
        p.moveTo(p.x(), (o.y()-pHeight-1) );
    }else if (dir == Up){
        p.moveTo(p.x(),o.y()+pHeight+1);
    }

}

Direction PhysicsUtils::reverseDirection(Direction dir){
    if(dir == Right){
        return Left;
    }else if (dir == Left){
        return Right;
    }else if (dir == Down){
        return Up;
    }else if (dir == Up){
        return Down;
    }
}
