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
    car->setPos(250,175);
}

void AccelerateView::keyPressEvent(QKeyEvent *e){
    QPointF point = car->pos();
    switch(e->key()){
        case Qt::Key_Up:
            point.setY(point.y()-10);
            break;
        case Qt::Key_Down:
            point.setY(point.y()+10);
            break;
        case Qt::Key_Left:
            point.setX(point.x()-10);
            break;
        case Qt::Key_Right:
             point.setX(point.x()+10);
            break;
    }
    car->setPos(point);
}

AccelerateView::~AccelerateView(){

}
