#include "accelerateview.h"

AccelerateView::AccelerateView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    QPixmap p = QPixmap(":ferrari.png");
    car = new SportsCar(p);
    scene->addItem(car);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    upPress = false;
    downPress = false;
    leftPress = false;
    rightPress = false;
    timer->start(100);
}

void AccelerateView::redraw(){
    if(upPress){
        car->accelerate();
    }
    if(downPress){
        car->reverse();
    }
    if(leftPress){
        car->leftTurn(6);
    }
    if(rightPress){
        car->rightTurn(6);
    }
    car->updatePosition();
}

void AccelerateView::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Up:
            upPress = true;
            break;
        case Qt::Key_Down:
            downPress = true;
            break;
        case Qt::Key_Left:
            leftPress = true;
            break;
        case Qt::Key_Right:
            rightPress = true;
            break;
    }

}

void AccelerateView::keyReleaseEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Up:
            upPress = false;
            break;
        case Qt::Key_Down:
            downPress = false;
            break;
        case Qt::Key_Left:
            leftPress = false;
            break;
        case Qt::Key_Right:
            rightPress = false;
            break;
    }

}

AccelerateView::~AccelerateView(){
    delete timer;
}
