#include "blockbreakerview.h"

#define PADDLEWIDTH 80
#define PADDLEHEIGHT 10
#define BLOCKWIDTH   60
#define PADDLESPEED 35.0

BlockBreakerView::BlockBreakerView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    blockCount = 0;
    this->setUpGameBoard();
    paddle = new Paddle(scene->width()/2-40,scene->height()-50,
                        PADDLEWIDTH,PADDLEHEIGHT);
    scene->addItem(paddle);
    this->setUpBlocks();

    projectile = NULL;
    ballInPlay = false;
    ballsRemaining = 5;
    score = 0;
    updateScore(score);
    updateBalls(ballsRemaining);
    rightPress = leftPress = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer->start(50);
    //this->winGame();
    //this->loseGame();
}

void BlockBreakerView::setUpBlocks(){
    for(int x=leftWall->boundingRect().width()+100;
        x+BLOCKWIDTH < rightWall->sceneBoundingRect().x() - 100;
    //for(int x=leftWall->boundingRect().width()+200;
    //    x+BLOCKWIDTH < rightWall->sceneBoundingRect().x()-150;
        x+=(BLOCKWIDTH+2) ){
        for(int y=this->scene()->height() - 275; y > 100; y-= PADDLEHEIGHT*2+2){
      //  for(int y=scene->height() - 300; y > 100; y-= PADDLEHEIGHT*2+2){
            StandardBlock *block = new StandardBlock(x,y,
                        BLOCKWIDTH,PADDLEHEIGHT*2);
            this->scene()->addItem(block);
            blockCount++;
        }

    }
}

void BlockBreakerView::setUpGameBoard(){
    topWall = new FixedRectangle(150, -15, this->scene()->width()-300, 25);
    topWall->setBrush(QBrush(Qt::black,Qt::SolidPattern));
    topWall->setPen(QPen(QColor(Qt::black)));
    this->scene()->addItem(topWall);

    leftWall = new FixedRectangle(0, 0, 150, this->scene()->height());
    leftWall->setBrush(QBrush(Qt::black,Qt::SolidPattern));
    leftWall->setPen(QPen(QColor(Qt::black)));
    this->scene()->addItem(leftWall);
    QGraphicsTextItem *scoreText = new QGraphicsTextItem();
    scoreText->setHtml("<h2><font color='white'>Score:</font></h2>");
    scoreText->setPos(50,10);
    this->scene()->addItem(scoreText);
    scoreField = new QGraphicsTextItem();
    //scoreField->setHtml("<h2><font color='white'>00</font></h2>");
    scoreField->setPos(65,45);
    this->scene()->addItem(scoreField);


    rightWall = new FixedRectangle(this->scene()->width()-150, 0, 150, this->scene()->height());
    rightWall->setBrush(QBrush(Qt::black,Qt::SolidPattern));
    rightWall->setPen(QPen(QColor(Qt::black)));
    this->scene()->addItem(rightWall);

    QGraphicsTextItem *ballsText = new QGraphicsTextItem();
    ballsText->setHtml("<h2><font color='white'>Balls:</font></h2>");
    ballsText->setPos(this->scene()->width() - ballsText->boundingRect().width()-50,10);
    this->scene()->addItem(ballsText);

    ballsField = new QGraphicsTextItem();
    //ballsField->setHtml("<h2><font color='white'>00</font></h2>");
    ballsField->setPos(this->scene()->width() - ballsText->boundingRect().width(),45);
    this->scene()->addItem(ballsField);

    bottomWall = new FixedRectangle(150, this->scene()->height()-10, this->scene()->width()-300, 25);
    bottomWall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    bottomWall->setPen(QPen(QColor(Qt::black)));
    this->scene()->addItem(bottomWall);
}

void BlockBreakerView::updateNumberField(QGraphicsTextItem *t, int num){
    QString result;
    QTextStream(&result) << "<h2><font color='white'>" << num
                         << "</font></h2>";
    t->setHtml(result);
}

void BlockBreakerView::updateScore(int num){
    updateNumberField(scoreField,num);
}

void BlockBreakerView::updateBalls(int num){
    updateNumberField(ballsField,num);
}


void BlockBreakerView::winGame(){
    if(projectile != NULL){
        this->scene()->removeItem(projectile);
    }
    this->gameOver(QString("<font color='blue'>You Win!</font>"));
}

void BlockBreakerView::loseGame(){
    this->gameOver(QString("<font color='red'>Game Over. You Lose</font>"));
}
void BlockBreakerView::gameOver(QString message){
    timer->stop();
    QGraphicsTextItem *text = new QGraphicsTextItem();
    text->setHtml("<table border='1'><td>"
                  "<h1>" + message + "</h1>"
                  "</td></table>");
    text->setPos(this->scene()->width()/2-text->boundingRect().width()/2,
                 100);

    this->scene()->addRect(QRectF(text->sceneBoundingRect()),QPen(Qt::black),QBrush(Qt::white));
    this->scene()->addItem(text);
}


void BlockBreakerView::redraw(){
    if (blockCount == 0){
        this->winGame();
    }
    if(leftPress){
        if((paddle->pos().x()) - PADDLESPEED > leftWall->boundingRect().width()){
            paddle->moveBy(-PADDLESPEED,0.0);
        }else{
            paddle->setPos(leftWall->boundingRect().width(),paddle->pos().y());
        }
    }
    if(rightPress){
        qreal rightWallStart = rightWall->boundingRect().x();
        if((paddle->pos().x()+PADDLEWIDTH) + PADDLESPEED < rightWallStart){
            paddle->moveBy(PADDLESPEED,0.0);
        }else{
            paddle->setPos(rightWallStart-PADDLEWIDTH,paddle->pos().y());
        }
    }
    this->updateProjectiles();
}

void BlockBreakerView::handleCollision(Projectile *p, Paddle *pad){
    //qreal centerDiff = pad->sceneBoundingRect().center().x() -
    //                       p->sceneBoundingRect().center().x();
    QVector2D pVelocity = p->getVelocity();
    QVector2D newPosition = p->getPosition();

    QVector2D impact = QVector2D(p->sceneBoundingRect().center().x() -
                                 pVelocity.x() -
                                 pad->sceneBoundingRect().center().x(),
                                 p->sceneBoundingRect().center().y() -
                                 pVelocity.y() -
                                 pad->sceneBoundingRect().center().y());
    newPosition.setY(pad->sceneBoundingRect().y() - p->boundingRect().height() - 1);
    p->setPosition(newPosition);
    p->setPos(newPosition.x(),newPosition.y());
    QVector2D deflectionVelocity = PhysicsUtils::resolveFixedCollision(pVelocity,impact);
    qreal yVel = deflectionVelocity.y();
    if( yVel > 0){
        deflectionVelocity.setY(-yVel);
    }else if (yVel > -5){
        deflectionVelocity.setY(-5.0);
    }
    p->setVelocity(deflectionVelocity);
}

void BlockBreakerView::handleCollision(Projectile * p,FixedRectangle *obstacle){
    if(obstacle == bottomWall){
        this->scene()->removeItem(p);
        ballInPlay = false;
        if(ballsRemaining < 1){
            this->loseGame();
            return;
        }
        ballsRemaining--;
        updateBalls(ballsRemaining);
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
        impact = QVector2D(pVelocity.x(),0.0);
    }else if(obstacle == topWall){
        newPosition.setY(obstacle->boundingRect().height() +  1);
        impact = QVector2D(0.0,pVelocity.y());
    }
    p->setPosition(newPosition);
    p->setPos(newPosition.x(),newPosition.y());
    QVector2D deflectionVelocity = PhysicsUtils::resolveFixedCollision(pVelocity,impact);
    p->setVelocity(deflectionVelocity);
}

void BlockBreakerView::handleCollision(Projectile * p, StandardBlock *block){

    QVector2D newPosition = p->getPosition();
    QVector2D pVelocity = p->getVelocity();
    QVector2D impact = pVelocity;
    QPointF last = QPointF(
            p->sceneBoundingRect().center().x() - pVelocity.x(),
            p->sceneBoundingRect().center().y() - pVelocity.y()
            );
    if (last.y() < block->sceneBoundingRect().y()){
        newPosition.setY(block->sceneBoundingRect().y() - p->sceneBoundingRect().height() -  1);
        impact = QVector2D(0.0,pVelocity.y());
    }else if(last.y() >  block->sceneBoundingRect().y()+ block->rect().height()){
        newPosition.setY(block->sceneBoundingRect().y() +  block->rect().height() + 1);
        impact = QVector2D(0.0,pVelocity.y());
    }else if(last.x() < block->sceneBoundingRect().x()){
        newPosition.setX(block->sceneBoundingRect().x() - p->sceneBoundingRect().width() - 1);
        impact = QVector2D(pVelocity.x(),0.0);
    }else{
        newPosition.setX(block->sceneBoundingRect().x() + block->rect().width() + 1);
        impact = QVector2D(pVelocity.x(),0.0);
    }
    //this->scene()->addLine(QLineF(last,p->sceneBoundingRect().center()),QPen(QColor(Qt::red)));
    p->setPosition(newPosition);
    p->setPos(newPosition.x(),newPosition.y());
    QVector2D deflectionVelocity = PhysicsUtils::resolveFixedCollision(pVelocity,impact);
    block->registerHit();
    score+=block->getPoints();
    this->updateScore(score);
    if(block->getHealth() < 1){
        blockCount--;
        this->scene()->removeItem(block);
    }
    p->setVelocity(deflectionVelocity);
}

void BlockBreakerView::updateProjectiles(){
    if(projectile != NULL){
       projectile->updatePosition();
       QList<QGraphicsItem *> collisions = projectile->collidingItems();
       bool hitBlock = false;
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
                   if(hitBlock == false){
                       this->handleCollision(projectile,sb);
                       hitBlock = true;
                   }
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
                projectile = paddle->launchBall(20,90);
                this->scene()->addItem(projectile);
                ballInPlay = true;
            }
            break;
        case Qt::Key_Left:
            leftPress = true;
            break;
        case Qt::Key_Right:
            rightPress = true;
            break;
    }
}

void BlockBreakerView::keyReleaseEvent(QKeyEvent *e){
     switch(e->key()){
        case Qt::Key_Left:
            leftPress = false;
            break;
        case Qt::Key_Right:
            rightPress = false;
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
