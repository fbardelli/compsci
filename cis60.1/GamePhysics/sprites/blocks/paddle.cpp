#include "paddle.h"

Paddle::Paddle(qreal x, qreal y, qreal width, qreal height) :
    BlockBase(x, y, width, height)
{

    this->setBrush(QBrush(QColor(123,45,67),Qt::SolidPattern));
    this->setPen(QPen(QColor(Qt::black)));
}


 Projectile * Paddle::launchBall(){
    qDebug() << "launching with rect" << this->rect();
    double radians = (25 * M_PI) /180;
    int horizontalOffset = (cos(radians) * 25);
    int verticalOffset = (sin(radians) * 25);
    Projectile * projectile = new Projectile(
            this->pos().x()+(this->rect().width()/2),
            this->pos().y()-this->rect().height(),
            25,
            35);
    projectile->pos().setY(projectile->pos().y()+projectile->boundingRect().height());
    projectile->setAcceleration(QVector2D(0.0,0.0));
    return projectile;
}
