#include "spaceship.h"

/**
  Constructs a new SpaceShip object and initializes all of its values
  */
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
    mainThruster = new QGraphicsPixmapItem(QPixmap(":ship-bthrust.png"),0, scene);
    mainThruster->setOpacity(0.25);
    this->addToGroup(mainThruster);
    this->setPos(scene->width()/2,scene->height() - ship->sceneBoundingRect().height());
    /*bounding = this->scene()->addRect(
        this->sceneBoundingRect(),
        QPen(QColor(Qt::black)),
        QBrush(QColor(75,0,130,25),Qt::SolidPattern)
    );*/
    angle = 0;
    verticalSpeed = horizontalSpeed = 0;
    mainThrusterOn = rightThrusterOn = leftThrusterOn = false;
}

/**
  Fires bottom thruster generating lift.  Thruster will glow while firing
  */
void SpaceShip::fireMainThruster(){
    mainThruster->setOpacity(1.0);
    if(verticalSpeed < 100){
        verticalSpeed +=4;
    }
    mainThrusterOn = true;
}

/**
  Fires left thruster which pushes the spaceship right, rotating the ship slightly.  Thruster will glow while firing
  */
void SpaceShip::fireLeftThruster(){
    leftThruster->setOpacity(1.0);
    if(horizontalSpeed < 50){
        horizontalSpeed +=2;
    }
    if(verticalSpeed < 100){
        verticalSpeed +=1;
    }
    if(angle < 15){
        this->rotate(5);
        angle += 5;
    }
    leftThrusterOn = true;
}


/**
  Fires left thruster which pushes the spaceship left, rotating the ship slightly.  Thruster will glow while firing
  */
void SpaceShip::fireRightThruster(){
    rightThruster->setOpacity(1.0);
    if(horizontalSpeed > -50){
        horizontalSpeed -=2;
    }
    if(verticalSpeed < 100){
        verticalSpeed +=1;
    }
    if(angle > -15){
        this->rotate(-5);
        angle -= 5;
    }
    rightThrusterOn = true;
}

/**
  Disables main thruster.
  */
void SpaceShip::cutMainThruster(){
    mainThruster->setOpacity(0.25);
    mainThrusterOn = false;
}

/**
  Disables left thruster.
  */
void SpaceShip::cutLeftThruster(){
    leftThruster->setOpacity(0.25);
    leftThrusterOn = false;
}

/**
  Disables right thruster.
  */
void SpaceShip::cutRightThruster(){
    rightThruster->setOpacity(0.25);
    rightThrusterOn = false;
}

/**
  When thrusters are not firing this routine resets the shit to a level position.
  */
void SpaceShip::levelSpaceship(){
    if(rightThrusterOn == false && angle < 0){
        this->rotate(5);
        angle += 5;
    }
    if(leftThrusterOn == false && angle > 0){
        this->rotate(-5);
        angle -= 5;
    }
}

/**
  Apply drag force reducing horizontal momentum.
  */
void SpaceShip::applyDrag(){
    if( horizontalSpeed > 0){
        horizontalSpeed--;
    }else if (horizontalSpeed < 0){
        horizontalSpeed++;
    }
}

QPointF SpaceShip::getNextPosition(QPointF point){
    if( (this->pos().x() + this->sceneBoundingRect().width() + horizontalSpeed) > this->scene()->width() ){
        point.setY(this->scene()->width() - this->sceneBoundingRect().width());
        horizontalSpeed = 0;
    }else if(this->pos().x() + horizontalSpeed < 0){
        point.setX(0);
        horizontalSpeed = 0;
    }else{
        point.setX(this->x() + this->horizontalSpeed);
    }
    if( (this->pos().y()+this->sceneBoundingRect().height()) < this->scene()->height() ){
        verticalSpeed -= (2 * 1.0);
    }
    if( (this->pos().y() + this->sceneBoundingRect().height() - verticalSpeed) > this->scene()->height() ){
        point.setY(this->scene()->height() - this->sceneBoundingRect().height());
        verticalSpeed = 0;
    }else if(this->pos().y()-verticalSpeed < 0){
        point.setY(0);
        verticalSpeed /= 2;
    }else{
        point.setY(this->y() - this->verticalSpeed);
    }
    return point;
}

/**
  Updates SpaceShip position on screen
  */
void SpaceShip::updatePosition(){
    QPointF point = this->pos();
    this->levelSpaceship();
    this->applyDrag();

    this->setPos(this->getNextPosition(point));
}

