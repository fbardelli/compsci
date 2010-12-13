#include "bouncyball.h"

BouncyBall::BouncyBall(int x, int y, QGraphicsView *w) : QObject(0)
{
    this->setAcceptDrops(true);
    this->setRect(0,0,50,50);
    this->setPos(x,y);
    QLinearGradient myGradient = QLinearGradient(0,0,40,40);
    myGradient.setColorAt(0, QColor(255,102,0));
    myGradient.setColorAt(1, QColor(255,25,0));
    QPen myPen;
    this->setPen(myPen);
    this->setBrush(myGradient);
    world = w;
    dragged = false;
    bounciness = 0.875;
    verticalSpeed = 0;
    emit bouncinessChanged(bounciness);
}

void BouncyBall::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        event->ignore();
        return;
    }
    dragged = true;
    this->setCursor(QCursor(Qt::ClosedHandCursor));
}

void BouncyBall::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    int x, y;
    if(event->scenePos().x() - 25 > 0) {
        if(event->scenePos().x() + 25 < world->rect().width()){
            x = event->scenePos().x() - 25;
        }else{
            x = this->x();
        }
    } else {
        x = 0;
    }
    if(event->scenePos().y() - 25 > 0) {
        if(event->scenePos().y() + 25 < world->rect().height()){
            y = event->scenePos().y() - 25;
        }else{
            y = this->y();
        }
    } else {
        y = 0;
    }
    this->setPos(x,y);
    this->setCursor(QCursor(Qt::OpenHandCursor));
}

/**
  Updates position of the ball based on the current vertical speed.  If a ground hit is detected, reverses speed based on current bounciness level
  */
void BouncyBall::updatePosition(){
    QPointF point = this->pos();

    if( (this->pos().y() + this->boundingRect().height()- verticalSpeed) > this->scene()->height() ){
        point.setY(this->scene()->height() - this->boundingRect().height());
        this->verticalSpeed = -(this->verticalSpeed * bounciness);
        if ((int)(this->verticalSpeed * bounciness) < (int)(this->verticalSpeed) ){
            this->verticalSpeed -= 1;
        }
    }else{
        point.setY(this->y() - this->verticalSpeed);
    }
    this->setPos(point);
}


/**
  @returns Current vertical speed of the ball.
  */
int BouncyBall::getVerticalSpeed(){
    return verticalSpeed;
}

/**
  @returns Current Bounciness of the ball
  */
float BouncyBall::getBounciness(){
    return bounciness;
}

/**
  Increase bounciness(elasticity) of the ball by increments of 0.125 up to a maximum of 1
  */
void BouncyBall::increaseBounciness(){
    if (bounciness < 1){
        bounciness += 0.125;
        emit bouncinessChanged(bounciness);
    }
}

/**
  Decrease bounciness(elasticity) of the ball by increments of 0.125 up to a minimum of 0
  */
void BouncyBall::decreaseBounciness(){
    if (bounciness > 0){
        bounciness -= 0.125;
        emit bouncinessChanged(bounciness);
    }
}

/**
  Apply the force of gravity to the bouncing ball, reducing vertical velocity
  */
void BouncyBall::applyGravity(){
    if(dragged){
        verticalSpeed = 0;
    } else {
        if( (this->pos().y()+this->boundingRect().height()) < this->scene()->height() ){
            verticalSpeed -= 4;
        }
    }
}


void BouncyBall::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    dragged = false;
    this->setCursor(QCursor(Qt::OpenHandCursor));
}
