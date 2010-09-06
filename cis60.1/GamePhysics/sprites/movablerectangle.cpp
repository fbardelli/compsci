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

void MovableRectangle::move(Direction dir,QList<MovableRectangle *> obstacles){
    QRectF r = _moveRect(dir);
    for (int i = 0; i < obstacles.size(); ++i) {
        if(PhysicsUtils::objectsCollide(r,obstacles.at(i)->rect->rect())){
            qDebug() << "Objects collide";
            PhysicsUtils::moveToEdge(r,obstacles.at(i)->rect->rect(),dir);
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
            }
            break;
        case Down:
            r.moveTo(r.x(),r.y()+velocity);
            if( (r.y() + r.height()) > boardHeight){
                r.moveTo(r.x(),boardHeight-r.height()-1);
            }
            break;
        case Left:
            r.moveTo(r.x()-velocity,r.y());
            if(r.x()-velocity < 0){
                r.moveTo(0,r.y());
            }
            break;
        case Right:
            r.moveTo(r.x()+velocity,r.y());
            if( (r.x() + r.width()) > boardWidth){
                r.moveTo(boardWidth - r.width()-1,r.y());
            }
            break;
        }
    return r;
}

