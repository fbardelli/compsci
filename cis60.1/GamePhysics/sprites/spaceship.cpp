#include "spaceship.h"

SpaceShip::SpaceShip(QGraphicsScene *scene) :
        QObject(0), QGraphicsItemGroup(0, scene)
{
    ship = new QGraphicsPixmapItem(QPixmap(":ship.png"),0, scene);
    this->addToGroup(ship);
    leftThruster = new QGraphicsPixmapItem(QPixmap(":ship-lthrust.png"),0, scene);
    leftThruster->setOpacity(0.25);
    this->addToGroup(leftThruster);
    rightThruster = new QGraphicsPixmapItem(QPixmap(":ship-rthrust.png"),0, scene);
    rightThruster->setOpacity(0.25);
    this->addToGroup(rightThruster);
    bottomThruster = new QGraphicsPixmapItem(QPixmap(":ship-bthrust.png"),0, scene);
    bottomThruster->setOpacity(0.25);
    this->addToGroup(bottomThruster);
    this->setPos(scene->width()/2,scene->height() - ship->boundingRect().height());
    angle = 0;
    verticalSpeed = horizontalSpeed = 0;
}

void SpaceShip::fireMainThruster(){
    bottomThruster->setOpacity(1.0);
    if(verticalSpeed < 100){
        verticalSpeed +=4;
    }
}

void SpaceShip::fireLeftThruster(){
    leftThruster->setOpacity(1.0);
    if(horizontalSpeed < 50){
        horizontalSpeed +=2;
    }
}

void SpaceShip::fireRightThruster(){
    rightThruster->setOpacity(1.0);
    if(horizontalSpeed > -50){
        horizontalSpeed -=2;
    }
}

void SpaceShip::cutMainThruster(){
    bottomThruster->setOpacity(0.25);
}

void SpaceShip::cutLeftThruster(){
    leftThruster->setOpacity(0.25);

}

void SpaceShip::cutRightThruster(){
    rightThruster->setOpacity(0.25);
}

void SpaceShip::updatePosition(){
    QPointF point = this->pos();
    if( horizontalSpeed > 0){
        horizontalSpeed--;
    }else if (horizontalSpeed < 0){
        horizontalSpeed++;
    }
    if( (this->pos().x() + this->boundingRect().width() + horizontalSpeed) > this->scene()->width() ){
        point.setY(this->scene()->width() - this->boundingRect().width());
        horizontalSpeed = 0;
    }else if(this->pos().x() + horizontalSpeed < 0){
        point.setX(0);
        horizontalSpeed = 0;
    }else{
        point.setX(this->x() + this->horizontalSpeed);
    }
    if( (this->pos().y()+this->boundingRect().height()) < this->scene()->height() ){
        verticalSpeed -= (2 * 1.0);
    }

    if( (this->pos().y() + this->boundingRect().height() - verticalSpeed) > this->scene()->height() ){
        point.setY(this->scene()->height() - this->boundingRect().height());
        verticalSpeed = 0;
    }else if(this->pos().y()-verticalSpeed < 0){
        point.setY(0);
        verticalSpeed /= 2;
    }else{
        point.setY(this->y() - this->verticalSpeed);
    }
    this->setPos(point);
    qDebug() << "pos is " << this->pos();
}

