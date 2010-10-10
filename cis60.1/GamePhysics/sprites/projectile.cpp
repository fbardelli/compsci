#include "projectile.h"

Projectile::Projectile(int x, int y, int angle, int velocity) :
x(x), y(y), angle(angle), velocity(velocity)
{
    /*velocity = v;
    x = x;
    y1 = y;
    theta = t;
    radius = 5;
    */

    double thetaRadians = (angle * M_PI) /180;
    horizontalVelocity = (cos(thetaRadians) * velocity);
    verticalVelocity = (sin(thetaRadians) * velocity);
    time = 0;
    this->setRect(0,0,20,20);
    this->setPos(x,y);
    QLinearGradient myGradient = QLinearGradient(0,0,40,40);
    QPen myPen;
    this->setPen(myPen);
    this->setBrush(myGradient);
}

void Projectile::updatePosition(){
    int x2 =  x + horizontalVelocity * time;
    int y2 =  y - verticalVelocity * time - 0.5 * (GRAVITY * time * time);
    this->setPos(x2,y2);
    time++;
}
