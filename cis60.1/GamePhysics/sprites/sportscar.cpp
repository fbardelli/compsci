#include "sportscar.h"
#define FRICTION 3

/**
           Create a new sports car

           @param pixmap    QPixmap containing graphic representation of this car
*/
SportsCar::SportsCar( const QPixmap &pixmap, QGraphicsItem *parent,
                      QGraphicsScene *scene)
     : QGraphicsPixmapItem(pixmap, parent, scene) {
    this->translate(this->boundingRect().width()/2,this->boundingRect().height()/2);
    currentAngle = 0;
    this->setPos(250,175);
    this->setOffset( -0.5 * QPointF(  this->boundingRect().width(), this->boundingRect().height() ) );
    speed = 0;
    topSpeed = 45;
    canTurn = true;
}

/**
           Apply the gas pedal increasing forward velocity towards the cars top speed

*/
void SportsCar::accelerate(){
    if(speed < topSpeed){
        speed += 6;
    }
    canTurn = true;
}

/**
           Apply the brake pedal reducing forward velocity, if car is stopped, puts car in reverse

*/
void SportsCar::reverse(){
    if(speed > -(topSpeed*0.5)){
        speed -= 5;
    }
    canTurn = true;
}

/**
           Turns the wheel left changing the cars heading

           @param degrees Degrees to turn the wheel

*/
void SportsCar::leftTurn(int degrees){
    if(canTurn){
        this->rotate(360-degrees);
        currentAngle = (currentAngle-degrees +360) % 360;
        //don't allow car to spin around when stopped
        if(abs(speed) < 5){
            canTurn = false;
        }
    }
}

/**
           Turns the wheel right changing the cars heading

           @param degrees Degrees to turn the wheel

*/
void SportsCar::rightTurn(int degrees){
    if(canTurn){
        this->rotate(degrees);
        currentAngle = (currentAngle+degrees) % 360;
        //don't allow car to spin around when stopped
        if(abs(speed) < 5){
            canTurn = false;
        }
    }
}

/**
           Update the cars postion based on current speed, current heading, and friction with the road

*/
void SportsCar::updatePosition(){
    QPointF point = this->pos();
    //Friction is always acting to decrease speed toward 0
    if(speed > 0){
        speed -= FRICTION;
    }else if (speed < 0){
        //fudging the friction value to avoid wobbling at very low speeds
        speed += (FRICTION - 1);
    }
    //update position based on current angle and speed
    //and make minor adjustment to the rotational center of sports car
    double currentRads = currentAngle * (M_PI / 180);
    double xDelta        = currentAngle % 180 == 90 ? 0 : cos(currentRads) * speed;
    double yDelta        = currentAngle % 180 == 0 ? 0  : sin(currentRads) * speed;
    this->setOffset( -0.5 * QPointF(  this->boundingRect().width(), this->boundingRect().height() ) );
    point.setY(point.y()+yDelta);
    point.setX(point.x()+xDelta);
    this->setPos(point);

}
