#include "blockbreakerview.h"

#define PADDLEWIDTH 50
#define PADDLEHEIGHT 20

BlockBreakerView::BlockBreakerView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    topWall = new FixedRectangle(150, 0, scene->width()-300, 25);
    topWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    topWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(topWall);

    leftWall = new FixedRectangle(0, 0, 150, scene->height());
    leftWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    leftWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(leftWall);

    rightWall = new FixedRectangle(scene->width()-150, 0, 150, scene->height());
    rightWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    rightWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(rightWall);

    bottomWall = new FixedRectangle(150, scene->height()-50, scene->width()-300, 50);
    bottomWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    bottomWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(bottomWall);

    paddle = new Paddle(scene->width()/2-25,scene->height()-75,
                        PADDLEWIDTH,PADDLEHEIGHT);
    scene->addItem(paddle);
    p = NULL;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer->start(100);
}

void BlockBreakerView::redraw(){
    this->updateProjectiles();
}

void BlockBreakerView::handleCollision(Projectile * p,FixedRectangle *obstacle){
    //handle collision with a wall covering the vertical plane
    QVector2D newPosition = p->getPosition();
    QVector2D pVelocity = p->getVelocity();
    QVector2D impact = pVelocity;
    qDebug()<<"startv p: " << p->pos() << " v: "<< p->getVelocity();
    //qDebug() << "op:" << obstacle->boundingRect().x() << " p:" << p->position.x();
    if(obstacle == rightWall){
        qDebug()<<"hit right";
        newPosition.setX(obstacle->boundingRect().x() - p->boundingRect().width() - 1);
        impact = QVector2D(pVelocity.x(),0.0);
        //impact = QVector2D(1.0,0.0);
        //pVelocity.setX(-pVelocity.x());
    }else if(obstacle == leftWall){
        qDebug()<<"hit left";
        newPosition.setX(obstacle->boundingRect().width() +  1);
        qDebug()<<"p: " << p->pos() << " v: "<< p->getVelocity();
        impact = QVector2D(pVelocity.x(),0.0);
        //pVelocity.setX(-pVelocity.x());
        //qDebug()<<"impact: " << impact;
    }else if(obstacle == topWall){
        qDebug()<<"hit top";
        newPosition.setY(obstacle->boundingRect().height() +  1);
        impact = QVector2D(0.0,pVelocity.y());
        //pVelocity.setY(-pVelocity.y());
    }else if(obstacle == bottomWall){
        qDebug()<<"hit bottom";
        newPosition.setY(obstacle->boundingRect().y() - p->boundingRect().height() - 1);
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
    if(p != NULL){
       p->updatePosition();
       QList<QGraphicsItem *> collisions = p->collidingItems();
       if(collisions.size() > 0){
           for (int i = 0; i < collisions.size(); ++i) {
               QGraphicsItem *ob = collisions.at(i);
               //p->resolveCollisionType(ob);
               FixedRectangle *fr;
               if( (fr = qgraphicsitem_cast<FixedRectangle *>(ob)) !=0){
                   this->handleCollision(p,fr);
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
            if (p == NULL){
                p = paddle->launchBall();
                this->scene()->addItem(p);
            }
            break;
        case Qt::Key_Left:
            qDebug() << "spx:" << paddle->scenePos().x();
            qDebug() << "spx:" << paddle->pos().x();
            qDebug() << "sbr:"  << paddle->sceneBoundingRect().x();

            if((paddle->pos().x()) - 25 > leftWall->boundingRect().width()){
                paddle->moveBy(-25.0,0.0);
            }else{
                paddle->setPos(leftWall->boundingRect().width(),paddle->pos().y());
            }
            break;
        case Qt::Key_Right:
            qreal rightWallStart = rightWall->boundingRect().x();
            if((paddle->pos().x()+PADDLEWIDTH) + 25 < rightWallStart){
                paddle->moveBy(25.0,0.0);
            }else{
                paddle->setPos(rightWallStart-PADDLEWIDTH,paddle->pos().y());
            }
            break;
    }
}

 BlockBreakerView::~BlockBreakerView(){
     delete timer;
}
