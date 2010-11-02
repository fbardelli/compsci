#include "jumpingman.h"

JumpingMan::JumpingMan( const QPixmap &pixmap,
                        QGraphicsScene *scene)
       : QObject(0), QGraphicsPixmapItem(pixmap, 0, scene){
      this->setOffset( -0.5 * QPointF(  this->boundingRect().width(), this->boundingRect().height() ) );
      this->setPos(50,scene->height()-this->boundingRect().height()/2);

      horizontalSpeed = 0;
      verticalSpeed = 0;
      jumping = false;
      facingRight = true;
}

void JumpingMan::moveForward() {
    horizontalSpeed = 5;
    if(!facingRight){
        this->scale(-1,1);
        facingRight=true;
    }
}

void JumpingMan::moveBackward(){
    horizontalSpeed = -5;
    if(facingRight){
        this->scale(-1,1);
        facingRight=false;
    }
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

void JumpingMan::applyGravity(double gravity){
    if( (this->pos().y()+this->boundingRect().height()) < this->scene()->height() ){
        verticalSpeed -= (4 * gravity);
    }
}

bool JumpingMan::isJumping(){
    return jumping;
}

void JumpingMan::jump(){
    if(!jumping){
        verticalSpeed = 30;
        jumping = true;
    }
}

void JumpingMan::updatePosition(){
    QPointF point = this->pos();
    point.setX(this->x() + this->horizontalSpeed);
    qDebug()<< "y is " << this->y() << " vspeed is " << this->verticalSpeed;
    if( (this->pos().y() + this->boundingRect().height()/2 - verticalSpeed) > this->scene()->height() ){
        point.setY(this->scene()->height() - this->boundingRect().height()/2);
        this->verticalSpeed = 0;
        this->jumping = false;
        emit landed();
    }else{
        point.setY(this->y() - this->verticalSpeed);
    }

    this->setPos(point);
}
