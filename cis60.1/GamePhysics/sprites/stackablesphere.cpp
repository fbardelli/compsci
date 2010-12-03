#include "stackablesphere.h"

StackableSphere::StackableSphere()
{
    this->setRect(0,0,40,40);
    //this->setPos(x,y);
    mass = 4.0;
    velocity = QVector2D(0.0,0.0);
    QLinearGradient myGradient = QLinearGradient(0,0,50,50);
    myGradient.setColorAt(0, QColor(0,102,255));
    myGradient.setColorAt(1, QColor(0,0,255));
    QPen myPen;
    this->setPen(myPen);
    this->setBrush(myGradient);
}

void StackableSphere::setMass(double m){
    mass = m;
}

double StackableSphere::getMass(){
    return mass;
}


void StackableSphere::setVelocity(QVector2D v){
    velocity = v;
}

QVector2D StackableSphere::getVelocity(){
    return velocity;
}
