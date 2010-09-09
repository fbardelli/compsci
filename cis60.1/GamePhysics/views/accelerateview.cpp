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
}

void AccelerateView::keyPressEvent(QKeyEvent *e){
    QPointF point = car->pos();
    double currentRads = currentAngle * (M_PI / 180);
    double xDelta        = currentAngle % 180 == 90 ? 0 : cos(currentRads) * 15;
    double yDelta        = currentAngle % 180 == 0 ? 0  : sin(currentRads) * 15;
    switch(e->key()){
        case Qt::Key_Up:
            point.setY(point.y()+yDelta);
            point.setX(point.x()+xDelta);
            car->setPos(point);
            break;
        case Qt::Key_Down:
            point.setY(point.y()+10);
            car->setPos(point);
            break;
        case Qt::Key_Left:
            //car->translate(car->boundingRect().width()/2,car->boundingRect().height()/2);
            car->rotate(360-6);
            /*car->setTransform(QTransform().translate(
                                            car->pos().x() - ( car->boundingRect().width()/2),
                                            car->pos().y() - ( car->boundingRect().height()/2)
                                          ).rotate(360-6));.translate(
                                                  -(car->pos().x() + ( car->boundingRect().width()/2)),
                                                  -(car->pos().y() + ( car->boundingRect().height()/2))
                                          ));*/
            currentAngle = (currentAngle-6 +360) % 360;
            break;
        case Qt::Key_Right:
            //car->translate(car->boundingRect().width()/2,car->boundingRect().height()/2);
            car->rotate(6);
            currentAngle = (currentAngle+6) % 360;
            break;
    }

    qDebug() << "\ncurrentAngle: " << currentAngle
             << "\ncurrent Rads: " << currentRads
             << "\ncurrent x:"     << car->pos().x()
             << "\ncurrent y:"     << car->pos().y()
             << "\nnew X:"         << xDelta
             << "\nnew Y:"         << yDelta
             << "\nbr width"       << car->boundingRect().width()
             << "\nbr height"      << car->boundingRect().height();

}

AccelerateView::~AccelerateView(){

}
