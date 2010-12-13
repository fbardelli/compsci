#include "stackablesphere.h"

/**
  Create a new spherical sprite that can be stacked on top of other spites of the same type
  */
StackableSphere::StackableSphere()
{
    this->setRect(0,0,40,40);
    //this->setPos(x,y);
    mass = 5.0;
    QLinearGradient myGradient = QLinearGradient(0,0,50,50);
    myGradient.setColorAt(0, QColor(0,102,255));
    myGradient.setColorAt(1, QColor(0,0,255));
    QPen myPen;
    velocity = QVector2D(0.0,0.0);
    acceleration = QVector2D(0.0,0.0);
    this->setPen(myPen);
    this->setBrush(myGradient);
    collisionState = false;
}

/**
           Reset the mass of the projectile

           param m    Value describing mass
*/
void StackableSphere::setMass(double m){
    mass = m;
}

/**
           Return the mass of the projectile

           @return    Value describing mass
*/
double StackableSphere::getMass(){
    return mass;
}

void StackableSphere::setID(int i){
    id = i;
}

int StackableSphere::getID(){
    return id;
}





/**
           Set the velocity of a StackableSphere

           @param    Vector describing Velocity
*/
void StackableSphere::setVelocity(QVector2D v){
    velocity = v;
}

/**
           Return the velocity of the StackableSphere

           @return    Vector describing current Velocity
*/
QVector2D StackableSphere::getVelocity(){
    return velocity;
}

/**
           Reset the acceleration of a StackableSphere

           @param    Vector describing acceleration
*/
void StackableSphere::setAcceleration(QVector2D a){
    acceleration = a;
}

/**
           Return the acceleration of a StackableSphere

           @return    Vector describing acceleration
*/
QVector2D StackableSphere::getAcceleration(){
    return acceleration;
}

/**
           Reset the position of a StackableSphere

           @param    Vector describing position
*/
void StackableSphere::setPosition(QVector2D p){
    position = p;
}

void StackableSphere::setCollisionState(bool s){
    collisionState = s;
}


QVector2D StackableSphere::getPosition(){
    return position;
}

void StackableSphere::applyGravity(){
}

/**
  Update the position of the StackableSphere, stop when we hit the floor or another StackableSphere
  */
void StackableSphere::updatePosition(){
    position += velocity;
    QList<QGraphicsItem *> collisions = this->collidingItems();
    bool objectsBelow = false;
    if(collisions.size() > 0){
        for (int i = 0; i < collisions.size(); ++i) {
            QGraphicsItem *ob = collisions.at(i);
            StackableSphere *ss;
            if( (ss = qgraphicsitem_cast<StackableSphere *>(ob)) !=0){
                if(ss->getPosition().y() > position.y()){
                    objectsBelow = true;
                    position.setY(ss->getPosition().y()-ss->boundingRect().height());
                }
            }
        }
    }
    if(!objectsBelow){
        velocity += QVector2D(0.0,8.7);
        position += velocity;
    }
    if(position.y()+velocity.y() + this->boundingRect().height() > this->scene()->height()){
        position.setY(this->scene()->height() - this->boundingRect().height() - 1);
    }

    this->setPos(position.x(),position.y());
}
