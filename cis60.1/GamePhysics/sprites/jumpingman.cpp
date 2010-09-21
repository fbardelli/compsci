#include "jumpingman.h"

JumpingMan::JumpingMan( const QPixmap &pixmap, QGraphicsItem *parent,
                        QGraphicsScene *scene)
       : QGraphicsPixmapItem(pixmap, parent, scene) {
      //this->translate(this->boundingRect().width()/2,this->boundingRect().height()/2);
      //this->rotate(180);
      this->setPos(250,175);
      this->setOffset( -0.5 * QPointF(  this->boundingRect().width(), this->boundingRect().height() ) );
      horizontalSpeed = 0;
      verticalSpeed = 0;
      jumping = false;
}

void JumpingMan::moveForward() {
    horizontalSpeed = 6;
}

void JumpingMan::moveBackward(){
    horizontalSpeed = -6;
}

int JumpingMan::getHorizonalSpeed(){
    return horizontalSpeed;
}

int JumpingMan::getVerticalSpeed(){
    return verticalSpeed;
}

void JumpingMan::stop(){
    horizontalSpeed = 0;
}

void JumpingMan::applyGravity(int gravity){
    if(this->y() > 0){
        verticalSpeed -= gravity;
    }
}

bool JumpingMan::isJumping(){
    return jumping;
}

void JumpingMan::jump(){
    verticalSpeed = 50;
    jumping = true;
}

void JumpingMan::updatePosition(){
    QPointF point = this->pos();
    point.setX(this->x()+this->horizontalSpeed);
    point.setY(this->y()-this->verticalSpeed);
}
