#include "blockbreakerview.h"

#define PADDLEWIDTH 50
#define PADDLEHEIGHT 20

BlockBreakerView::BlockBreakerView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    topWall = new FixedRectangle(50, 0, scene->width()-100, 50);
    topWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    topWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(topWall);

    leftWall = new FixedRectangle(0, 0, 50, scene->height());
    leftWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    leftWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(leftWall);

    rightWall = new FixedRectangle(scene->width()-50, 0, 50, scene->height());
    rightWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    rightWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(rightWall);

    bottomWall = new FixedRectangle(50, scene->height()-50, scene->width()-100, 50);
    bottomWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    bottomWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(bottomWall);

    paddle = new Paddle(scene->width()/2-25,scene->height()-75,
                        PADDLEWIDTH,PADDLEHEIGHT);
    scene->addItem(paddle);
    p = NULL;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer->start(125);
}

void BlockBreakerView::redraw(){
    this->updateProjectiles();
}

void BlockBreakerView::handleCollision(Projectile * p,FixedRectangle *obstacle){
    //handle collision with a wall covering the vertical plane
    QVector2D impact = QVector2D(0.0,0.0);
    QVector2D position = p->getPosition();
    QVector2D pVelocity = p->getVelocity();
    //qDebug() << "op:" << obstacle->boundingRect().x() << " p:" << p->position.x();
    if(obstacle == rightWall){
        qDebug()<<"hit right";
        p->setPos(obstacle->boundingRect().x() - p->boundingRect().width() - 1,
                  p->pos().y()
                  );
        impact = QVector2D(pVelocity.x(),0);
    }else if(obstacle == leftWall){
        qDebug()<<"hit left";
        p->setPos(obstacle->boundingRect().width() + obstacle->pos().x() + 1,
                  p->pos().y()
                  );
        impact = QVector2D(pVelocity.x(),0);
    }else if(obstacle == topWall){
        qDebug()<<"hit top";
        p->setPos(p->pos().x(),
                  obstacle->boundingRect().height() + p->boundingRect().y() + 1
                  );
        impact = QVector2D(0,pVelocity.y());
    }else if(obstacle == bottomWall){
        qDebug()<<"hit bottom";
        p->setPos(p->pos().x(),
                  obstacle->boundingRect().height() - p->boundingRect().y() - 1
                  );
        impact = QVector2D(0,pVelocity.y());
    }
    QVector2D deflectionVelocity = PhysicsUtils::resolveFixedCollision(pVelocity,impact);
    p->setVelocity(deflectionVelocity);
}


void BlockBreakerView::updateProjectiles(){
    if(p != NULL){
       p->updatePosition();
       QList<QGraphicsItem *> collisions = p->collidingItems();
       if(collisions.size() > 0){
           for (int i = 0; i < collisions.size(); ++i) {
               QGraphicsItem *ob = collisions.at(i);
               p->resolveCollisionType(ob);
               FixedRectangle *fr;
               if( (fr = qgraphicsitem_cast<FixedRectangle *>(ob)) !=0){
                   this->handleCollision(p,fr);
               }else{
                   p->handleCollision(ob);
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

            if((paddle->pos().x()) - 25 > 0){
                paddle->moveBy(-25.0,0.0);
            }else{
                paddle->setPos(0.0,paddle->pos().y());
            }
            break;
        case Qt::Key_Right:
            qreal sceneWidth = this->scene()->width();
            if((paddle->pos().x()+PADDLEWIDTH) + 25 < sceneWidth){
                paddle->moveBy(25.0,0.0);
            }else{
                paddle->setPos(sceneWidth-PADDLEWIDTH,paddle->pos().y());
            }
            break;
    }
}

 BlockBreakerView::~BlockBreakerView(){
     delete timer;
}
