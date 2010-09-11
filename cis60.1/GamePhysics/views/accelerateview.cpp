#include "accelerateview.h"

AccelerateView::AccelerateView(QGraphicsScene *scene,QWidget *parent)
{
    this->setParent(parent);
    this->setScene(scene);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,parent->width(),parent->height());
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
