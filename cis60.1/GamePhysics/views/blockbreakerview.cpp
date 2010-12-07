#include "blockbreakerview.h"

#define PADDLEWIDTH 80
#define PADDLEHEIGHT 10
#define PADDLESPEED 35.0

BlockBreakerView::BlockBreakerView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    topWall = new FixedRectangle(150, 0, scene->width()-300, 10);
    topWall->setBrush(QBrush(Qt::black,Qt::SolidPattern));
    topWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(topWall);

    leftWall = new FixedRectangle(0, 0, 150, scene->height());
    leftWall->setBrush(QBrush(Qt::black,Qt::SolidPattern));
    leftWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(leftWall);

    rightWall = new FixedRectangle(scene->width()-150, 0, 150, scene->height());
    rightWall->setBrush(QBrush(Qt::black,Qt::SolidPattern));
    rightWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(rightWall);

    bottomWall = new FixedRectangle(150, scene->height()-10, scene->width()-300, 10);
    bottomWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    bottomWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(bottomWall);

    paddle = new Paddle(scene->width()/2-40,scene->height()-50,
                        PADDLEWIDTH,PADDLEHEIGHT);
    scene->addItem(paddle);
    projectile = NULL;
    ballInPlay = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer->start(100);
}

void BlockBreakerView::redraw(){
    this->updateProjectiles();
}

void BlockBreakerView::handleCollision(Projectile *p, Paddle *pad){
    qreal centerDiff = pad->sceneBoundingRect().center().x() -
                           p->sceneBoundingRect().center().x();

    QVector2D pVelocity = p->getVelocity();
    QVector2D newPosition = p->getPosition();
    qDebug() << "hit paddle with velocity " << pVelocity
             << " centerdiff "<< centerDiff << " *radius* " << pad->sceneBoundingRect().width()/2;
    qDebug() << "pbr:" << pad->boundingRect() << "psbr:" << pad->sceneBoundingRect();

    newPosition.setY(pad->sceneBoundingRect().y() - p->boundingRect().height() - 1);
    QVector2D impact = QVector2D(0.0,pVelocity.y());
    p->setPosition(newPosition);
    p->setPos(newPosition.x(),newPosition.y());
    QVector2D deflectionVelocity = PhysicsUtils::resolveFixedCollision(pVelocity,impact);
    p->setVelocity(deflectionVelocity);
}

void BlockBreakerView::handleCollision(Projectile * p,FixedRectangle *obstacle){
    if(obstacle == bottomWall){
        this->scene()->removeItem(p);
        qDebug()<< "removed:" << p;
        ballInPlay = false;
        return;
        //qDebug()<<"hit bottom";
        //newPosition.setY(obstacle->boundingRect().y() - p->boundingRect().height() - 1);
        //impact = QVector2D(0.0,pVelocity.y());
        //pVelocity.setY(-pVelocity.y());
    }
    //handle collision with a wall covering the vertical plane
    QVector2D newPosition = p->getPosition();
    QVector2D pVelocity = p->getVelocity();
    QVector2D impact = pVelocity;
    //qDebug()<<"startv p: " << p->pos() << " v: "<< p->getVelocity();
    //qDebug() << "op:" << obstacle->boundingRect().x() << " p:" << p->position.x();
    if(obstacle == rightWall){
        //qDebug()<<"hit right";
        newPosition.setX(obstacle->boundingRect().x() - p->boundingRect().width() - 1);
        impact = QVector2D(pVelocity.x(),0.0);
        //impact = QVector2D(1.0,0.0);
        //pVelocity.setX(-pVelocity.x());
    }else if(obstacle == leftWall){
        //qDebug()<<"hit left";
        newPosition.setX(obstacle->boundingRect().width() +  1);
        qDebug()<<"p: " << p->pos() << " v: "<< p->getVelocity();
        impact = QVector2D(pVelocity.x(),0.0);
        //pVelocity.setX(-pVelocity.x());
        //qDebug()<<"impact: " << impact;
    }else if(obstacle == topWall){
        //qDebug()<<"hit top";
        newPosition.setY(obstacle->boundingRect().height() +  1);
        impact = QVector2D(0.0,pVelocity.y());
        //pVelocity.setY(-pVelocity.y());
    }
    p->setPosition(newPosition);
    p->setPos(newPosition.x(),newPosition.y());
    //p->updatePosition();
    //p->setPos(newPosition.x(),newPosition.y());
    QVector2D deflectionVelocity = PhysicsUtils::resolveFixedCollision(pVelocity,impact);
    p->setVelocity(deflectionVelocity);
    //p->setVelocity(pVelocity);
    qDebug()<<"endv p: " << p->pos() << " v: "<< p->getVelocity();
}


void BlockBreakerView::updateProjectiles(){
    if(projectile != NULL){
       projectile->updatePosition();
       QList<QGraphicsItem *> collisions = projectile->collidingItems();
       if(collisions.size() > 0){
           for (int i = 0; i < collisions.size(); ++i) {
               QGraphicsItem *ob = collisions.at(i);
               //p->resolveCollisionType(ob);
               FixedRectangle *fr;
               Paddle *pdl;
               if( (fr = qgraphicsitem_cast<FixedRectangle *>(ob)) !=0){
                   this->handleCollision(projectile,fr);
               }else if( (pdl = qgraphicsitem_cast<Paddle *>(ob)) !=0){
                   this->handleCollision(projectile,pdl);
               }else{
                   //p->handleCollision(ob);
               }

           }
       }
    }
}

void BlockBreakerView::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Space:
            if (! ballInPlay ){
                projectile = paddle->launchBall();
                qDebug()<<"adding new p:" << projectile;
                this->scene()->addItem(projectile);
                ballInPlay = true;
            }
            break;
        case Qt::Key_Left:
            qDebug() << "spx:" << paddle->scenePos().x();
            qDebug() << "spx:" << paddle->pos().x();
            qDebug() << "sbr:"  << paddle->sceneBoundingRect().x();

            if((paddle->pos().x()) - PADDLESPEED > leftWall->boundingRect().width()){
                paddle->moveBy(-PADDLESPEED,0.0);
            }else{
                paddle->setPos(leftWall->boundingRect().width(),paddle->pos().y());
            }
            break;
        case Qt::Key_Right:
            qreal rightWallStart = rightWall->boundingRect().x();
            if((paddle->pos().x()+PADDLEWIDTH) + PADDLESPEED < rightWallStart){
                paddle->moveBy(PADDLESPEED,0.0);
            }else{
                paddle->setPos(rightWallStart-PADDLEWIDTH,paddle->pos().y());
            }
            break;
    }
}

BlockBreakerView::~BlockBreakerView(){
     delete timer;
}
