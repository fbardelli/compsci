#include "cannon.h"

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
}

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
            70);
    this->scene()->addItem(projectile);
    projectiles.append(projectile);
}

void Cannon::updateProjectiles(){
    QListIterator<Projectile *> i(projectiles);
    Projectile *p;
    while (i.hasNext()){
        p = i.next();
        p->updatePosition();
        QList<QGraphicsItem *> collisions = p->collidingItems();
        if(collisions.size() > 0){
            qDebug() << "collision detected!";
            for (int i = 0; i < collisions.size(); ++i) {
                QGraphicsItem *ob = collisions.at(i);
                qDebug() << "type:"  << ob->type();
                FixedRectangle *fr;
                if( (fr = qgraphicsitem_cast<FixedRectangle *>(ob)) !=0){
                    p->handleCollision(fr);
                }else{
                    qDebug() << ob;
                    p->handleCollision(ob);
                }

            }
        }
    }
}


void Cannon::incline(){
    if(angle < 90){
        cannonbarrel->rotate(-5);
        angle+=5;
    }
}
void Cannon::decline(){
    if(angle > -5){
        cannonbarrel->rotate(5);
        angle-=5;
    }
}
