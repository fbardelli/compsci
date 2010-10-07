#include "cannon.h"

Cannon::Cannon(QGraphicsScene *scene) :
    QObject(0), QGraphicsItemGroup(0, scene)
{
    cannonbarrel = new QGraphicsPixmapItem(QPixmap(":cannonbarrel.png"),0, scene);
    this->addToGroup(cannonbarrel);
    cannonbase = new QGraphicsPixmapItem(QPixmap(":cannonbase.png"),0, scene);
    this->addToGroup(cannonbase);
    cannonbarrel->setOffset( -0.5 * QPointF(  cannonbase->boundingRect().width(), cannonbase->boundingRect().height() ) );
    cannonbarrel->setX(cannonbarrel->x()+55);
    cannonbarrel->setY(cannonbarrel->y()+25);
    this->setY(scene->height() - cannonbase->boundingRect().height());
}

void Cannon::incline(){
    cannonbarrel->rotate(-5);
}
void Cannon::decline(){
    cannonbarrel->rotate(5);
}
