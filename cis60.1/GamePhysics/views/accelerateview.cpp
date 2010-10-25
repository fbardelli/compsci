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

const QString AccelerateView::getInstructions(){
    return QString(
        "This example demonstrates acceleration and friction.  Holding the accelerator will cause the car "
        "to gradually speed up.  Releasing the accelerator will cause the car to slow down."
        "<table border='1' cellpadding='1' cellspacing='1'>"
            "<tr><th>Key</th><th>Action</th></tr>"
            "<tr><td>Up</td><td>Accelerate, moving the car forward</td></tr>"
            "<tr><td>Down</td><td>Reverse, reduces speed if car is moving forward.  If car is stopped, move car backwards</td></tr>"
            "<tr><td>Left</td><td>Turn wheels toward the left (relative to the direction the car is facing)</td></tr>"
            "<tr><td>Right</td><td>Turn wheels toward the right (relative to the direction the car is facing)</td></tr>"
        "</table>"
    );

}

AccelerateView::~AccelerateView(){
    delete timer;
}
