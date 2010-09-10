#include "accelerateview.h"

AccelerateView::AccelerateView(QGraphicsScene *scene,QWidget *parent)
{
    this->setParent(parent);
    this->setScene(scene);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,parent->width(),parent->height());
    QPixmap carImage = QPixmap(":ferrari.png");
    car = scene->addPixmap(carImage);
    car->translate(car->boundingRect().width()/2,car->boundingRect().height()/2);
    car->rotate(180);
    currentAngle = 0;
    car->setPos(250,175);
    car->setOffset( -0.5 * QPointF(  car->boundingRect().width(), car->boundingRect().height() ) );
    speed = 0;
    canTurn = true;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(decelerate()));
    timer->start(250);
}

void AccelerateView::decelerate() {
    QPointF point = car->pos();
    if(speed > 0){
        speed -= 3;
    }else if (speed < 0){
        speed += 2;
    }
    double currentRads = currentAngle * (M_PI / 180);
    double xDelta        = currentAngle % 180 == 90 ? 0 : cos(currentRads) * speed;
    double yDelta        = currentAngle % 180 == 0 ? 0  : sin(currentRads) * speed;
    car->setOffset( -0.5 * QPointF(  car->boundingRect().width(), car->boundingRect().height() ) );
    point.setY(point.y()+yDelta);
    point.setX(point.x()+xDelta);
    car->setPos(point);
}

void AccelerateView::keyPressEvent(QKeyEvent *e){

    switch(e->key()){
        case Qt::Key_Up:
            if(speed < 40){
                speed += 6;
            }
            canTurn = true;
            break;
        case Qt::Key_Down:
            if(speed > -15){
                speed -= 5;
            }
            canTurn = true;
            break;
        case Qt::Key_Left:
            //car->translate(car->boundingRect().width()/2,car->boundingRect().height()/2);
            if(canTurn){
                car->rotate(360-6);
                currentAngle = (currentAngle-6 +360) % 360;
                if(speed < 5){
                    canTurn = false;
                }
            }
            break;
        case Qt::Key_Right:
            //car->translate(car->boundingRect().width()/2,car->boundingRect().height()/2);
            if(canTurn){
                car->rotate(6);
                currentAngle = (currentAngle+6) % 360;
                if(speed < 5){
                    canTurn = false;
                }

            }
            break;
    }
    /*
    qDebug() << "\ncurrentAngle: " << currentAngle
             << "\ncurrent Rads: " << currentRads
             << "\ncurrent x:"     << car->pos().x()
             << "\ncurrent y:"     << car->pos().y()
             << "\nnew X:"         << xDelta
             << "\nnew Y:"         << yDelta
             << "\nbr width"       << car->boundingRect().width()
             << "\nbr height"      << car->boundingRect().height();
             */

}

AccelerateView::~AccelerateView(){

}
