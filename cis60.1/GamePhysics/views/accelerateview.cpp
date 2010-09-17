#include "accelerateview.h"

AccelerateView::AccelerateView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    QPixmap p = QPixmap(":ferrari.png");
    car = new SportsCar(p);
    scene->addItem(car);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer->start(250);
}

void AccelerateView::redraw(){
    car->updatePosition();
}

void AccelerateView::keyPressEvent(QKeyEvent *e){

    switch(e->key()){
        case Qt::Key_Up:
            car->accelerate();
            break;
        case Qt::Key_Down:
            car->reverse();
            break;
        case Qt::Key_Left:
            car->leftTurn(6);
            break;
        case Qt::Key_Right:
            car->rightTurn(6);
            break;
    }

}

AccelerateView::~AccelerateView(){
    delete timer;
}
