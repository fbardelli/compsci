#include "projectile.h"

Projectile::Projectile(int x, int y, int angle, int velocity) :
x(x), y(y), angle(angle), velocity(velocity)
{

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
    lastX = this->pos().x();
    lastY = this->pos().y();
    int x2 =  x + horizontalVelocity * time;
    int y2 =  y - verticalVelocity * time - 0.5 * (GRAVITY * time * time);
    this->setPos(x2,y2);
    time++;
}

void Projectile::handleCollision(FixedRectangle *obstacle){
    //handle collision with a wall covering the vertical plane
    if(obstacle->boundingRect().x() > this->boundingRect().x() + this->boundingRect().width()){
        //
        //determine the angle of impact based on previous position
        int currentX = this->pos().x();
        int currentY = this->pos().y();
        int xDelta = currentX - lastX;
        int yDelta = currentY - lastY;
        double currentRadian = (double)-yDelta/(double)xDelta;
        double impactAngle = currentRadian * (180 / M_PI);
        qDebug() << "reverse time!  x is " << currentX << " lastX is "<< lastX
                 << "  y is " << currentY << " lastY is "<< lastY
                 << " xDelta is " << xDelta << " yDelta is " << yDelta
                 << " projectile angle is "  << angle
                 << " impact angle is " << impactAngle
                 << " relaunch angle is "  << ( 180 + (impactAngle*2));

        //reset projectile course
        //180 degrees == perpendicular to our vertical wall
        double thetaRadians = ( (180 + (impactAngle*2)) * M_PI) /180;
        //assume projectile loses %70 of energy on impact and update
        // velocities with new angle.
        velocity *= 0.3;
        horizontalVelocity = (cos(thetaRadians) * velocity);
        verticalVelocity = (sin(thetaRadians) * velocity);
        x = (int)(obstacle->boundingRect().x() - this->boundingRect().width() -1);
        y = lastY;
        //reset starting position outside the bounds of the obstacle
        this->setPos(x,y);
        qDebug() << "relaunch!  x is " << x << "  y is " << y
                 << " horizontalVelocity " << horizontalVelocity
                 << " verticalVelocity " << verticalVelocity;
        //set time to 1 as we've already rendered the 0th position
        time = 1;
    }
}

void Projectile::handleCollision(QGraphicsItem *obstacle){
    //handle collision with a generic moving item
    /*
    if(obstacle->boundingRect().x() > this->boundingRect().x() + this->boundingRect().width()){
        //
        //determine the angle of impact based on previous position
        int currentX = this->pos().x();
        int currentY = this->pos().y();
        int xDelta = currentX - lastX;
        int yDelta = currentY - lastY;
        double currentRadian = (double)-yDelta/(double)xDelta;
        double impactAngle = currentRadian * (180 / M_PI);
        qDebug() << "reverse time!  x is " << currentX << " lastX is "<< lastX
                 << "  y is " << currentY << " lastY is "<< lastY
                 << " xDelta is " << xDelta << " yDelta is " << yDelta
                 << " projectile angle is "  << angle
                 << " impact angle is " << impactAngle
                 << " relaunch angle is "  << ( 180 + (impactAngle*2));

        //reset projectile course
        //180 degrees == perpendicular to our vertical wall
        double thetaRadians = ( (180 + (impactAngle*2)) * M_PI) /180;
        //assume projectile loses %70 of energy on impact and update
        // velocities with new angle.
        velocity *= 0.3;
        horizontalVelocity = (cos(thetaRadians) * velocity);
        verticalVelocity = (sin(thetaRadians) * velocity);
        x = (int)(obstacle->boundingRect().x() - this->boundingRect().width() -1);
        y = lastY;
        //reset starting position outside the bounds of the obstacle
        this->setPos(x,y);
        qDebug() << "relaunch!  x is " << x << "  y is " << y
                 << " horizontalVelocity " << horizontalVelocity
                 << " verticalVelocity " << verticalVelocity;
        //set time to 1 as we've already rendered the 0th position
        time = 1;
    }
    */
}


