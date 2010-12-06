#include "paddle.h"

Paddle::Paddle(qreal x, qreal y, qreal width, qreal height) :
    BlockBase(x, y, width, height)
{

    this->setBrush(QBrush(QColor(123,45,67),Qt::SolidPattern));
    this->setPen(QPen(QColor(Qt::black)));
}


 Projectile * Paddle::launchBall(){
    Projectile * projectile = new Projectile(
            this->pos().x()+(this->rect().width()/2),
            this->pos().y()+1,
            90,
            70);
    projectile->setAcceleration(QVector2D(0.0,0.0));
    return projectile;
}
