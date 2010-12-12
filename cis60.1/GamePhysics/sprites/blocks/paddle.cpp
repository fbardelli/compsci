#include "paddle.h"

Paddle::Paddle(qreal x, qreal y, qreal width, qreal height) :
    BlockBase(x, y, width, height)
{

    this->setBrush(QBrush(QColor(123,45,67),Qt::SolidPattern));
    this->setPen(QPen(QColor(Qt::black)));
}


 Projectile * Paddle::launchBall(int speed,int angle){
    //double radians = (angle * M_PI) /180;
    //int horizontalOffset = (cos(radians) * angle);
    //int verticalOffset = (sin(radians) * angle);
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
