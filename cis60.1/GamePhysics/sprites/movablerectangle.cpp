#include "movablerectangle.h"

MovableRectangle::MovableRectangle(QGraphicsRectItem *rect,
                                   int m, int v,
                                   Direction dir,
                                   QGraphicsView *w) : mass(m), velocity(v), direction(dir)
{
    this->rect = rect;
    this->world = w;
}

void MovableRectangle::move(){
    move(direction);
}

void MovableRectangle::move(Direction dir){
    direction = dir;
    this->rect->setRect(_moveRect(dir));
}

void MovableRectangle::move(QList<MovableRectangle *> obstacles){
    move(direction,obstacles);
}

void MovableRectangle::move(Direction dir,QList<MovableRectangle *> obstacles){
    QRectF r = _moveRect(dir);
    for (int i = 0; i < obstacles.size(); ++i) {
        MovableRectangle *ob = obstacles.at(i);
        if (ob == this){
            continue;
        }
        if(PhysicsUtils::objectsCollide(r,ob->rect->rect())){
            if(this->mass <= ob->mass){
                PhysicsUtils::moveToEdge(r,obstacles.at(i)->rect->rect(),dir);
            }else{
                QRectF oRect = ob->rect->rect();
                PhysicsUtils::moveToEdge(oRect,r,PhysicsUtils::reverseDirection(dir));
                ob->rect->setRect(oRect);
            }
        }
    }
    this->rect->setRect(r);
}


QRectF MovableRectangle::_moveRect(Direction dir){
    QRectF r = this->rect->rect();
    int boardHeight = this->world->height();
    int boardWidth  = this->world->width();
    switch(dir){
        case Up:
            r.moveTo(r.x(),r.y()-velocity);
            if(r.y() < 0){
                r.moveTo(r.x(),0);
                this->direction = PhysicsUtils::reverseDirection(this->direction);
            }
            break;
        case Down:
            r.moveTo(r.x(),r.y()+velocity);
            if( (r.y() + r.height()) > boardHeight){
                r.moveTo(r.x(),boardHeight-r.height()-1);
                this->direction = PhysicsUtils::reverseDirection(this->direction);
            }
            break;
        case Left:
            r.moveTo(r.x()-velocity,r.y());
            if(r.x()-velocity < 0){
                r.moveTo(0,r.y());
                this->direction = PhysicsUtils::reverseDirection(this->direction);
            }
            break;
        case Right:
            r.moveTo(r.x()+velocity,r.y());
            if( (r.x() + r.width()) > boardWidth){
                r.moveTo(boardWidth - r.width()-1,r.y());
                this->direction = PhysicsUtils::reverseDirection(this->direction);
            }
            break;
        }
    return r;
}

