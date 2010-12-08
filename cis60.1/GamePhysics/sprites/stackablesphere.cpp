#include "stackablesphere.h"

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

void StackableSphere::setMass(double m){
    mass = m;
}

double StackableSphere::getMass(){
    return mass;
}

void StackableSphere::setID(int i){
    id = i;
}

int StackableSphere::getID(){
    return id;
}

void StackableSphere::setVelocity(QVector2D v){
    velocity = v;
}

QVector2D StackableSphere::getVelocity(){
    return velocity;
}

void StackableSphere::setAcceleration(QVector2D a){
    acceleration = a;
}

QVector2D StackableSphere::getAcceleration(){
    return acceleration;
}

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

void StackableSphere::updatePosition(){
    //QVector2D position = QVector2D(this->pos());
    //velocity += acceleration;
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
                //this->setPos(this->pos().x(),ss->pos().y()-ss->boundingRect().height()-2);
                /*
                QVector2D obCenter = QVector2D(ss->sceneBoundingRect().center());
                QVector2D pCenter = QVector2D(this->sceneBoundingRect().center());
                QVector2D obVelocity = ss->getVelocity();
                qDebug() << "obV:" << obVelocity;
                QVector2D vDiff  = velocity - obVelocity;
                qDebug() << "vdiff:"<< vDiff;
                QVector2D impact = QVector2D(obCenter-pCenter);
                qDebug() << "impact:"<<impact;
                QVector2D un = PhysicsUtils::componentVector(vDiff,impact);
                qDebug() << "un:"<<(un);
                QVector2D ut = vDiff - un;
                qDebug() << "ut:"<<(ut);
                qDebug()<<"(ut+obVelocity)"<<"("<<ut<<"+"<<obVelocity<<"):"<<(ut+obVelocity);
                velocity = ut+obVelocity;
                qDebug()<<"(un+obVelocity)"<<"("<<un<<"+"<<obVelocity<<"):"<<(un+obVelocity);
                //this->setPos(position.x(),position.y());
                ss->setVelocity((un+obVelocity));
                //ss->setAcceleration(acceleration);
                ss->updatePosition();
                */
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
