#include "paddle.h"


/**
 Creates a new Paddle object

 @param x x postion the Paddle will start at
 @param y y postion the Paddle will start at
 @param width Width of the Paddle
 @param height Height of the Paddle

*/
Paddle::Paddle(qreal x, qreal y, qreal width, qreal height) :
    BlockBase(x, y, width, height)
{

    this->setBrush(QBrush(QColor(123,45,67),Qt::SolidPattern));
    this->setPen(QPen(QColor(Qt::black)));
}

/**
 launches a new ball from the top of the Paddle at the speed and angle supplied

 @param speed Number of pixels per update the ball should move at
 @param angle Angle relative to the top surface of the paddle (e.g. 90 degrees is perpendicular to the Paddle)
 @returns a point to a new Projectile object
*/
 Projectile * Paddle::launchBall(int speed,int angle){
    Projectile * projectile = new Projectile(
            this->pos().x()+(this->rect().width()/2),
            this->pos().y()-this->rect().height(),
            angle,
            speed);
    projectile->pos().setY(
            projectile->pos().y() -
            projectile->boundingRect().height()
    );
    projectile->setAcceleration(QVector2D(0.0,0.0));
    return projectile;
}
