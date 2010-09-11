#include "sportscar.h"

SportsCar::SportsCar( const QPixmap &pixmap, QGraphicsItem *parent,
                      QGraphicsScene *scene)
     : QGraphicsPixmapItem(pixmap, parent, scene) {
    this->translate(this->boundingRect().width()/2,this->boundingRect().height()/2);
    this->rotate(180);
    currentAngle = 0;
    this->setPos(250,175);
    this->setOffset( -0.5 * QPointF(  this->boundingRect().width(), this->boundingRect().height() ) );
    speed = 0;
    topSpeed = 40;
    canTurn = true;
}



void SportsCar::accelerate(){
    if(speed < topSpeed){
        speed += 6;
    }
    canTurn = true;
}

void SportsCar::reverse(){
    if(speed > -(topSpeed*0.5)){
        speed -= 5;
    }
    canTurn = true;
}

void SportsCar::leftTurn(int degrees){
    if(canTurn){
        this->rotate(360-degrees);
        currentAngle = (currentAngle-degrees +360) % 360;
        if(abs(speed) < 5){
            canTurn = false;
        }
    }
}

void SportsCar::rightTurn(int degrees){

    if(canTurn){
        this->rotate(degrees);
        currentAngle = (currentAngle+degrees) % 360;
        if(abs(speed) < 5){
            canTurn = false;
        }

    }
}

void SportsCar::updatePosition(){
    QPointF point = this->pos();
    if(speed > 0){
        speed -= 3;
    }else if (speed < 0){
        speed += 2;
    }
    double currentRads = currentAngle * (M_PI / 180);
    double xDelta        = currentAngle % 180 == 90 ? 0 : cos(currentRads) * speed;
    double yDelta        = currentAngle % 180 == 0 ? 0  : sin(currentRads) * speed;
    this->setOffset( -0.5 * QPointF(  this->boundingRect().width(), this->boundingRect().height() ) );
    point.setY(point.y()+yDelta);
    point.setX(point.x()+xDelta);
    this->setPos(point);

}
