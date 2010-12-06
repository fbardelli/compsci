#include "projectile.h"



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

void Projectile::setVelocity(QVector2D v){
    this->pVelocity = v;
}

QVector2D Projectile::getVelocity(){
    //qDebug() << "pv: " << pVelocity << " qv:" <<  QVector2D(horizontalVelocity,verticalVelocity);
    //return QVector2D(horizontalVelocity,verticalVelocity);
    return pVelocity;
}

QVector2D Projectile::getInitialVelocity(){
    return initialVelocity;
}


void Projectile::setPosition(QVector2D p){
    position = p;
}

QVector2D Projectile::getPosition(){
    return QVector2D(this->pos());
}

QVector2D Projectile::getAcceleration(){
    return acceleration;
}

void Projectile::setAcceleration(QVector2D a){
    this->acceleration = a;
}

void Projectile::updatePosition(){
    lastPosition = position;
    pVelocity += acceleration;
    position += pVelocity;
    this->setPos(position.x(),position.y());
}

/*double Projectile::getImpactAngle(){
    int currentX = this->pos().x();
    int currentY = this->pos().y();
    int xDelta = currentX - lastX;
    int yDelta = currentY - lastY;
    double currentRadian = (double)-yDelta/(double)xDelta;
    double impactAngle = currentRadian * (180 / M_PI);
    return impactAngle;
}*/

void Projectile::handleCollision(FixedRectangle *obstacle){
    //handle collision with a wall covering the vertical plane
    qDebug() << "op:" << obstacle->boundingRect().x() << " p:" << this->position.x();
    if(obstacle->boundingRect().x() < this->position.x() + this->boundingRect().width()){
        position.setX( obstacle->boundingRect().x() - this->boundingRect().width() - 1);
        this->setPos(position.x(),position.y());
        QVector2D impact = QVector2D(pVelocity.x(),0);
        QVector2D deflectionVelocity = PhysicsUtils::resolveFixedCollision(pVelocity,impact);
        deflectionVelocity *= 0.5;
        this->setVelocity(deflectionVelocity);
    }
}

void Projectile::handleCollision(StackableSphere *obstacle){
        /*
        //this->scene()->addLine(QLineF(center,obCenter),QPen(QColor(Qt::red)));
        double massDiff  = this->getMass()/obstacle->getMass();
        QVector2D vDiff  = this->getVelocity() - obstacle->getVelocity();
        qDebug() << "vdiff:"<<vDiff;
        QVector2D un     = componentVector(vDiff,this->getVelocity());
        qDebug() << "un:"<<(un);
        QVector2D ut     = vDiff - un;
        qDebug() << "ut:"<<(ut);
        QVector2D vn     = un * (massDiff-1)/(massDiff+1);
        qDebug() << "vn:"<<(vn);
        QVector2D wn     = un * 2 * massDiff /(massDiff+1);
        qDebug() << "wn:"<<(wn);
        qDebug() << "v:"<< this->getVelocity();
        qDebug() << "new v:"<<(ut+vn);
        this->setVelocity(ut+vn);
        obstacle->setVelocity(wn*-1);*/
        double massDiff  = this->getMass()/obstacle->getMass();
        QVector2D obCenter = QVector2D(obstacle->sceneBoundingRect().center());
        QVector2D pCenter = QVector2D(this->sceneBoundingRect().center());
        QVector2D obVelocity = obstacle->getVelocity();
        qDebug() << "obV:"<<obVelocity;
        QVector2D vDiff  = this->getVelocity() - obVelocity;
        qDebug() << "vdiff:"<<vDiff;
        QVector2D impact = QVector2D(obCenter-pCenter);
        qDebug() << "impact:"<<impact;
        QVector2D un     = PhysicsUtils::componentVector(vDiff,impact);
        qDebug() << "un:"<<(un);
        QVector2D ut     = vDiff - un;
        QVector2D vn     = un * (massDiff-1)/(massDiff+1);
        QVector2D wn     = un * 2 * massDiff /(massDiff+1);
        qDebug() << "ut:"<<(ut);
        qDebug()<<"(ut+obVelocity)"<<"("<<ut<<"+"<<obVelocity<<"):"<<(ut+obVelocity);
        //this->setVelocity((ut+obVelocity));
        this->setVelocity((ut+vn));
        this->updatePosition();
        qDebug()<<"(un+obVelocity)"<<"("<<un<<"+"<<obVelocity<<"):"<<(un+obVelocity);
        //obstacle->setVelocity((un+obVelocity));
        obstacle->setVelocity(wn);
        obstacle->updatePosition();

    /*set u to obj1 . velocity-obj 2.velocity
    set un to componentVector(u,n)
    set ut to u-un
    set obj1 . velocity to ut+obj 2. velocity
    set obj2. velocity to un+obj 2. velocity*/
}


void Projectile::handleCollision(QGraphicsItem *obstacle){

}


void Projectile::resolveCollisionType(QGraphicsItem *ob){
    FixedRectangle *fr;
    StackableSphere *ss;
    if( (fr = qgraphicsitem_cast<FixedRectangle *>(ob)) !=0){
        this->handleCollision(fr);
    }else if( (ss = qgraphicsitem_cast<StackableSphere *>(ob)) !=0){
        this->handleCollision(ss);
    }else{
        //qDebug() << ob;
        this->handleCollision(ob);
    }
}

void Projectile::setMass(double m){
    mass = m;
}

double Projectile::getMass(){
    return mass;
}
