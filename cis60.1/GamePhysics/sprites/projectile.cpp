#include "projectile.h"

QVector2D componentVector(QVector2D vector, QVector2D directionVector);

QVector2D normalVector (QVector2D vector);

double component (QVector2D vector, QVector2D directionVector);

double magnitude(QVector2D v);


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

QVector2D Projectile::getPosition(){
    return QVector2D(this->pos());
}

void Projectile::updatePosition(){
    lastX = this->pos().x();
    lastY = this->pos().y();
    pVelocity += acceleration;
    position += pVelocity;
    this->setPos(position.x(),position.y());
}

double Projectile::getImpactAngle(){
    int currentX = this->pos().x();
    int currentY = this->pos().y();
    int xDelta = currentX - lastX;
    int yDelta = currentY - lastY;
    double currentRadian = (double)-yDelta/(double)xDelta;
    double impactAngle = currentRadian * (180 / M_PI);
    return impactAngle;
}

void Projectile::handleCollision(FixedRectangle *obstacle){
    //handle collision with a wall covering the vertical plane
    qDebug() << "op:" << obstacle->boundingRect().x() << " p:" << this->position.x();
    if(obstacle->boundingRect().x() < this->position.x() + this->boundingRect().width()){
        position.setX( obstacle->boundingRect().x() - this->boundingRect().width() - 1);
        this->setPos(position.x(),position.y());
        QVector2D impact = QVector2D(pVelocity.x(),0);
        QVector2D c     = componentVector(pVelocity,impact);
        QVector2D deflectionVelocity = pVelocity - 2*c;
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
        QVector2D obCenter = QVector2D(obstacle->sceneBoundingRect().center());
        QVector2D pCenter = QVector2D(this->sceneBoundingRect().center());
        QVector2D obVelocity = obstacle->getVelocity();
        qDebug() << "obV:"<<obVelocity;
        QVector2D vDiff  = this->getVelocity() - obVelocity;
        qDebug() << "vdiff:"<<vDiff;
        QVector2D impact = QVector2D(obCenter-pCenter);
        qDebug() << "impact:"<<impact;
        QVector2D un     = componentVector(vDiff,impact);
        qDebug() << "un:"<<(un);
        QVector2D ut     = vDiff - un;
        qDebug() << "ut:"<<(ut);
        qDebug()<<"(ut+obVelocity)"<<(ut+obVelocity);
        this->setVelocity((ut+obVelocity));
        qDebug()<<"(un+obVelocity)"<<(un+obVelocity);
        obstacle->setVelocity((un+obVelocity));

    /*set u to obj1 . velocity-obj 2.velocity
    set un to componentVector(u,n)
    set ut to u-un
    set obj1 . velocity to ut+obj 2. velocity
    set obj2. velocity to un+obj 2. velocity*/
}

QVector2D normalVector (QVector2D vector){
   return QVector2D(-vector.y(),vector.x());
}

QVector2D componentVector(QVector2D vector, QVector2D directionVector){
    QVector2D v  = directionVector.normalized();
    //return v * QVector2D::dotProduct(vector,directionVector);
    return ( v * component(vector, directionVector));
}

double component (QVector2D vector, QVector2D directionVector){
    double alpha = atan2(directionVector.y(), directionVector.x());
    double theta = atan2(vector.y(),vector.x());
    qDebug() << "alpha:" << alpha << " theta:" << theta;
    double mag   = magnitude(vector);
    double a     = mag*cos(theta-alpha);
    return a;
}

double magnitude(QVector2D v){
  double s = 0;
  s+= v.x()*v.x();
  s+= v.y()*v.y();
  return sqrt(s);
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
/*
function component ( vector, directionVector)
  set alpha to atan(directionVector [2] , directionVector [1 ] )
  set theta to atan(vector[ 2] ,vector[1 ] )
  set mag to magnitude( vector)
  set a to mag*cos( theta-alpha)
  return a
end function

function componentVector( vector, directionVector)
  set v to norm(directionVector)
  return component( vector, directionVector) *v
end function

function normalVector (vector)
return vector(- vector[ 2] , vector[ 1 ])
end function

function resolveFixedCollision(obj , n)
  set c to componentVector(obj. velocity, n)
  set obj. velocity to v- 2*c
end function

function intersectionPoint(a, b, c, d)
    set tc1 to b[1 ] - a[1 ]
    set tc2 to b[2] - a[2]
    set sc1 to c[1 ] - d[1 ]
    set sc2 to c[2] - s[2]
    set con1 to c[ 1 ] - a[1 ]
    set con2 to c[ 2] - a[2]
    set det to (tc2*sc1 -tc1*sc2)
    if det=0 then return " no unique solution"
    set con to tc2*con1 -tc1*con2
    set s to con/det
    return c+s*(d-c)
end function

function resolveCollisionFree1 (obj 1 , obj 2, n)
    set r to obj1 . mass/obj 2. mass
    set un to componentVector(obj1 . velocity, n)
    set ut to obj1 . velocity-un
    set vn to un*(r- 1 )/(r+1)
    set wn to un*2*r/ (r+1 )
    set obj1 . velocity to ut+vn
    set obj2. velocity to wn
end function

function resolveCollisionFree (obj 1 , obj 2, n)
    set r to obj1 . mass/obj 2. mass
    set u to obj1 . velocity-obj 2.velocity
    set un to componentVector(u,n)
    set ut to u-un
    set vn to un*(r- 1 )/(r+1)
    set wn to un*2*r/ (r+1 )
    set obj1 . velocity to ut+vn+u2
    set obj2. velocity to wn+u2
end function

function resolveCollisionEqualMass ( obj 1 , obj 2, n)
    set u to obj1 . velocity-obj 2.velocity
    set un to componentVector(u,n)
    set ut to u-un
    set obj1 . velocity to ut+obj 2. velocity
    set obj2. velocity to un+obj 2. velocity
end function

function resolveInelasticCollisionFree (obj 1 , obj 2, n)
    set r to obj1 . mass/obj 2. mass
    set u to obj1 . velocity-obj 2.velocity
    set e to obj1 . efficiency*obj2. efficiency
    set un to component ( u,n)
    set ut to mag(u- un*n)
    set sq to r*r*un*un-( r+1 ) *( (r-e) *un*un+(1 - e) *ut*ut))
    set vn to n*(sqrt(sq) - r*un) /(r+1 )
    set wn to r*(n*un-vn)
    set obj1 . velocity to ut+vn+ obj 2. velocity
    set obj2. velocity to wn+ obj2. velocity
end function

function resolveInelasticCollisionFixed ( obj 1 , obj 2, n)
    set e to obj1 . efficiency*obj2. efficiency
    set un to component ( obj 1 . velocity, n)
    set ut to mag(obj 1. velocity -un*n)
    set sq to  (e*un*un+( e-1 ) *ut*ut) )
    set vn to n*sqrt( sq)
    set obj1 . velocity to ut+vn
end function

function addVectors (v1, v2)
   // assume v1 and v2 are arrays of the same length
   set newVector to an empty array
   repeat for i=1 to the length of v1
      append v1[i]+v2[i] to newVector
   end repeat
   return newVector
end function

function scaleVector (v, s)
   repeat for i=1 to the length of v
      multiply v[i] by s
   end repeat
   return v
end function

function magnitude (v)
   set s to 0
   repeat with i=1 to the length of v
      add v[i]*v[i] to s
   end repeat
   return sqrt(s)
end function

function norm (v)
   set m to magnitude(v)
   if m=0 then return "error" // you can't normalize a zero vector
   return scaleVector(v,1/m)
end function

*/
