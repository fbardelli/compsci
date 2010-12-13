#include "projectile.h"


/**
           Create a new projectile

           @param x    Starting x position
           @param y    Starting y position
           @param angle Angle the projectile is fired at
           @param velocity Starting velocity the projectile is fired at, this will be converted to a vector based on angle of fire
*/
Projectile::Projectile(int x, int y, int angle, int velocity) :
x(x), y(y), angle(angle), velocity(velocity)
{

    position = QVector2D(x,y);
    acceleration = QVector2D(0,4.7);
    double thetaRadians = (angle * M_PI) /180;
    horizontalVelocity = (cos(thetaRadians) * velocity);
    verticalVelocity = -(sin(thetaRadians) * velocity);
    pVelocity = initialVelocity = QVector2D(horizontalVelocity, verticalVelocity);
    mass = 5.0;
    this->setRect(0,0,20,20);
    this->setPos(x,y);
    QLinearGradient myGradient = QLinearGradient(0,0,40,40);
    QPen myPen;
    this->setPen(myPen);
    this->setBrush(myGradient);
}


/**
           Reset the velocity of the projectile

           @param v    Vector describing new Velocity
*/
void Projectile::setVelocity(QVector2D v){
    this->pVelocity = v;
}

/**
           Return the velocity of a projectile

           @return    Vector describing current Velocity
*/
QVector2D Projectile::getVelocity(){
    return pVelocity;
}

/**
           Return the velocity of a projectile at time of fire

           @return    Vector describing initial Velocity
*/
QVector2D Projectile::getInitialVelocity(){
    return initialVelocity;
}

/**
           Reset the current position of the projectile

           @param p    Vector describing new Position
*/
void Projectile::setPosition(QVector2D p){
    position = p;
}

/**
           Return the position of the projectile

           @return    Vector describing current Position
*/
QVector2D Projectile::getPosition(){
    return QVector2D(this->pos());
}

/**
           Return the acceleration of a projectile, generally used to apply gravity to the projectile

           @return    Vector describing acceleration
*/
QVector2D Projectile::getAcceleration(){
    return acceleration;
}

/**
           Resets the acceleration of a projectile

           @param a    Vector describing acceleration
*/
void Projectile::setAcceleration(QVector2D a){
    this->acceleration = a;
}

/**
           Apply velocity and acceleration to projectile changing its position
*/
void Projectile::updatePosition(){
    lastPosition = position;
    pVelocity += acceleration;
    position += pVelocity;
    this->setPos(position.x(),position.y());
}

/**
           Resolves the collision of the projectile with a FixedRectangle (wall)

           @param obstacle    FixedRectangle the projecile hit
*/
QVector2D Projectile::handleCollision(FixedRectangle *obstacle){
    QVector2D newVelocity = this->getVelocity();
    if(obstacle->boundingRect().x() < this->position.x() + this->boundingRect().width()){
        position.setX( obstacle->boundingRect().x() - this->boundingRect().width() - 1);
        this->setPos(position.x(),position.y());
        QVector2D impact = QVector2D(pVelocity.x(),0);
        newVelocity = PhysicsUtils::resolveFixedCollision(pVelocity,impact);
        newVelocity *= 0.5;
    }
    return newVelocity;
}

/**
           Resolves the collision of the projectile with a StackableSphere

           @param obstacle    StackableSphere the projecile hit
*/
QVector2D Projectile::handleCollision(StackableSphere *obstacle){
        QVector2D newVelocity = this->getVelocity();
        double massDiff  = this->getMass()/obstacle->getMass();
        QVector2D obCenter = QVector2D(obstacle->sceneBoundingRect().center());
        QVector2D pCenter = QVector2D(this->sceneBoundingRect().center());
        QVector2D obVelocity = obstacle->getVelocity();
        QVector2D vDiff  = this->getVelocity() - obVelocity;
        QVector2D impact = QVector2D((obCenter-obVelocity)-pCenter);
        QVector2D un     = PhysicsUtils::componentVector(vDiff,impact);
        QVector2D ut     = vDiff - un;
        QVector2D vn     = un * (massDiff-1)/(massDiff+1);
        QVector2D wn     = un * 2 * massDiff /(massDiff+1);
        newVelocity = (ut+vn);
        obstacle->setVelocity(wn);
        obstacle->updatePosition();
        return newVelocity;
}


QVector2D Projectile::handleCollision(QGraphicsItem *obstacle){
    return this->getVelocity();

}

/**
           Determine and execute the correct collision for a generic obstacle

           @param ob    QGraphicsItem hit by the projectile
           @returns new velocity of the current projectile post collision
*/
QVector2D Projectile::resolveCollisionType(QGraphicsItem *ob){
    FixedRectangle *fr;
    StackableSphere *ss;
    QVector2D newVelocity = this->getVelocity();
    if( (fr = qgraphicsitem_cast<FixedRectangle *>(ob)) !=0){
        newVelocity = this->handleCollision(fr);
    }else if( (ss = qgraphicsitem_cast<StackableSphere *>(ob)) !=0){
        newVelocity = this->handleCollision(ss);
    }else{
        newVelocity = this->handleCollision(ob);
    }
    return newVelocity;
}


/**
           Reset the mass of the projectile

           param m    Value describing mass
*/
void Projectile::setMass(double m){
    mass = m;
}

/**
           Return the mass of the projectile

           @return    Value describing mass
*/
double Projectile::getMass(){
    return mass;
}
