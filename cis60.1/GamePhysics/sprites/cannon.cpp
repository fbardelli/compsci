#include "cannon.h"
/**
  Creat new cannon object
  */
Cannon::Cannon(QGraphicsScene *scene) :
    QObject(0), QGraphicsItemGroup(0, scene)
{
    cannonbarrel = new QGraphicsPixmapItem(QPixmap(":cannonbarrel.png"),0, scene);
    this->addToGroup(cannonbarrel);
    cannonbase = new QGraphicsPixmapItem(QPixmap(":cannonbase.png"),0, scene);
    this->addToGroup(cannonbase);
    cannonbarrel->setOffset( -0.5 * QPointF(  cannonbase->boundingRect().width(), cannonbase->boundingRect().height() ) );
    cannonbarrel->setPos(cannonbarrel->x()+55,cannonbarrel->y()+25);
    this->setPos(this->x(),scene->height() - cannonbase->boundingRect().height());
    angle = 0;
    projectileSpeed = 70;
}

/**
  Sets the initial speed at which cannon Projectiles will leave the barrel
  @param speed Projectile speed
  */
void Cannon::setProjectileSpeed(int speed){
    projectileSpeed = speed;
}

/**
  Fire new Projectile from cannon at the current projectileSpeed
  Projectile start position is adjusted to match the end of the cannon barrel
  */
void Cannon::fire(){
    //Start centered at 50,50 from the bottom right, adjust position
    //to match the angle of the barrel
    double radians = (angle * M_PI) /180;
    int horizontalOffset = (cos(radians) * 100);
    int verticalOffset = (sin(radians) * 100);
    Projectile * projectile = new Projectile(
            35+horizontalOffset,
            this->scene()->height()-68-verticalOffset,
            angle,
            projectileSpeed);
    this->scene()->addItem(projectile);
    projectiles.append(projectile);
}

/**
  Modify the position of all active projectiles,
  */
void Cannon::updateProjectiles(){
    QListIterator<Projectile *> i(projectiles);
    Projectile *p;
    while (i.hasNext()){
        p = i.next();
        p->updatePosition();
        QList<QGraphicsItem *> collisions = p->collidingItems();
        if(collisions.size() > 0){
            //qDebug()<<"collision size:"<<collisions.size();
            QVector2D newVelocity = p->getVelocity();
            for (int i = 0; i < collisions.size(); ++i) {
                QGraphicsItem *ob = collisions.at(i);
                newVelocity = p->resolveCollisionType(ob);
            }
            p->setVelocity(newVelocity);
        }
    }
}

/**
  increases the angle of incline on the Cannon barrel to a maximum of 90 degrees, changing the angle new Projectiles will be fired at
*/
void Cannon::raise(){
    if(angle < 90){
        cannonbarrel->rotate(-5);
        angle+=5;
    }
}

/**
  decreases the angle of incline on the Cannon barrel to a minimum of -5 degrees, changing the angle new Projectiles will be fired at
*/
void Cannon::lower(){
    if(angle > -5){
        cannonbarrel->rotate(5);
        angle-=5;
    }
}
