#include "blockbreakerview.h"

#define PADDLEWIDTH 80
#define PADDLEHEIGHT 10
#define PADDLESPEED 35.0

BlockBreakerView::BlockBreakerView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    topWall = new FixedRectangle(150, -15, scene->width()-300, 25);
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

    bottomWall = new FixedRectangle(150, scene->height()-10, scene->width()-300, 25);
    bottomWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    bottomWall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(bottomWall);

    paddle = new Paddle(scene->width()/2-40,scene->height()-50,
                        PADDLEWIDTH,PADDLEHEIGHT);
    StandardBlock *bl1 = new StandardBlock(scene->width()/2-40,scene->height()-250,
                        PADDLEWIDTH,PADDLEHEIGHT*2);
    StandardBlock *bl2 = new StandardBlock(scene->width()/2-40+PADDLEWIDTH,scene->height()-250,
                        PADDLEWIDTH,PADDLEHEIGHT*2);
    scene->addItem(paddle);
    scene->addItem(bl1);
    scene->addItem(bl2);

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

    QVector2D impact = QVector2D(p->sceneBoundingRect().center().x() -
                                 pVelocity.x() -
                                 pad->sceneBoundingRect().center().x(),
                                 p->sceneBoundingRect().center().y() -
                                 pVelocity.y() -
                                 pad->sceneBoundingRect().center().y());
    qDebug() << "impact velocity:" << impact;
    newPosition.setY(pad->sceneBoundingRect().y() - p->boundingRect().height() - 1);
    //QVector2D impact = QVector2D(0.0,pVelocity.y());
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
    }
    //handle collision with a wall covering the vertical plane
    QVector2D newPosition = p->getPosition();
    QVector2D pVelocity = p->getVelocity();
    QVector2D impact = pVelocity;
    if(obstacle == rightWall){
        newPosition.setX(obstacle->boundingRect().x() - p->boundingRect().width() - 1);
        impact = QVector2D(pVelocity.x(),0.0);
    }else if(obstacle == leftWall){
        newPosition.setX(obstacle->boundingRect().width() +  1);
        qDebug()<<"p: " << p->pos() << " v: "<< p->getVelocity();
        impact = QVector2D(pVelocity.x(),0.0);
    }else if(obstacle == topWall){
        newPosition.setY(obstacle->boundingRect().height() +  1);
        impact = QVector2D(0.0,pVelocity.y());
    }
    p->setPosition(newPosition);
    p->setPos(newPosition.x(),newPosition.y());
    QVector2D deflectionVelocity = PhysicsUtils::resolveFixedCollision(pVelocity,impact);
    p->setVelocity(deflectionVelocity);
    qDebug()<<"endv p: " << p->pos() << " v: "<< p->getVelocity();
}

void BlockBreakerView::handleCollision(Projectile * p, StandardBlock *block){
    qDebug()<< "hitblock on ";

    QVector2D newPosition = p->getPosition();
    QVector2D pVelocity = p->getVelocity();
    QVector2D impact = pVelocity;
    QPointF last = QPointF(
            p->sceneBoundingRect().center().x() - pVelocity.x(),
            p->sceneBoundingRect().center().y() - pVelocity.y()
            );
    if (last.y() < block->sceneBoundingRect().y()){
       qDebug() << "top";
        newPosition.setY(block->sceneBoundingRect().y() - p->sceneBoundingRect().height() -  1);
        impact = QVector2D(0.0,pVelocity.y());
    }else if(last.y() >  block->sceneBoundingRect().y()+ block->rect().height()){
        newPosition.setY(block->sceneBoundingRect().y() +  block->rect().height() + 1);
        impact = QVector2D(0.0,pVelocity.y());
        qDebug() << "bottom";
    }else if(last.x() < block->sceneBoundingRect().x()){
        qDebug() << "left";
        newPosition.setX(block->sceneBoundingRect().x() - p->sceneBoundingRect().width() - 1);
        impact = QVector2D(pVelocity.x(),0.0);
    }else{
        qDebug() << "right";
        newPosition.setX(block->sceneBoundingRect().x() + block->rect().width() + 1);
        impact = QVector2D(pVelocity.x(),0.0);
    }
    //this->scene()->addLine(QLineF(last,p->sceneBoundingRect().center()),QPen(QColor(Qt::red)));
    p->setPosition(newPosition);
    p->setPos(newPosition.x(),newPosition.y());
    QVector2D deflectionVelocity = PhysicsUtils::resolveFixedCollision(pVelocity,impact);
    block->registerHit();
    if(block->getHealth() < 1){
        this->scene()->removeItem(block);
    }
    p->setVelocity(deflectionVelocity);
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
               StandardBlock *sb;
               if( (fr = qgraphicsitem_cast<FixedRectangle *>(ob)) !=0){
                   this->handleCollision(projectile,fr);
               }else if( (pdl = qgraphicsitem_cast<Paddle *>(ob)) !=0){
                   this->handleCollision(projectile,pdl);
               }else if( (sb = qgraphicsitem_cast<StandardBlock *>(ob)) !=0){
                   this->handleCollision(projectile,sb);
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
                projectile = paddle->launchBall(90);
                qDebug()<<"adding new p:" << projectile;
                this->scene()->addItem(projectile);
                ballInPlay = true;
            }
            break;
        case Qt::Key_Left:
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

const QString BlockBreakerView::getInstructions(){
    return QString(
        "This example demonstrates a simple game that employs various "
        "collision detection and resolution techniques developed in earlier "
        "examples "
        "<br/><table border='1' cellpadding='1' cellspacing='1'>"
            "<tr><th>Key</th><th>Action</th></tr>"
            "<tr><td>Right</td><td>Move Paddle towards right wall</td></tr>"
            "<tr><td>Left</td><td>Move Paddle towards left wall</td></tr>"
            "<tr><td>Space</td><td>Create New Ball(if no ball is in play)</td></tr>"
        "</table>"
    );

}

BlockBreakerView::~BlockBreakerView(){
     delete timer;
}
