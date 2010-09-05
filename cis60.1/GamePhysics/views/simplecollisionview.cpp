#include "simplecollisionview.h"

#define SQUARE_SIZE 50
#define MOVE_DISTANCE 10

SimpleCollisionView::SimpleCollisionView(QGraphicsScene *scene,QWidget *parent)
{
    this->setParent(parent);
    this->setScene(scene);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,parent->width(),parent->height());
    player = new MovableRectangle(
                scene->addRect(
                    QRectF(0, 0, SQUARE_SIZE, SQUARE_SIZE),
                    QPen(QColor(Qt::black)),
                    QBrush(Qt::red,Qt::SolidPattern)),
                10,
                MOVE_DISTANCE,
                Left,
                this);

    for (int x = 75; x < parent->width(); x += 150) {
        for(int y = 0; y < parent->height(); y+= 150) {
            QGraphicsRectItem *obstacle;
            obstacle = scene->addRect(QRectF(x, y, SQUARE_SIZE, SQUARE_SIZE),QPen(QColor(Qt::black)),QBrush(Qt::blue,Qt::SolidPattern));
            obstacles.push_back(obstacle);
        }

    }
}


void SimpleCollisionView::keyPressEvent(QKeyEvent *e){
    QRectF r = player->rect->rect();
    Direction dir;
    switch(e->key()){
        case Qt::Key_Up:
            dir = Up;
            break;
        case Qt::Key_Down:
            dir = Down;
            break;
        case Qt::Key_Left:
            dir = Left;
            break;
        case Qt::Key_Right:
            dir = Right;
            break;
    }
    r = player->move(dir);
    for (int i = 0; i < obstacles.size(); ++i) {
        if(PhysicsUtils::objectsCollide(r,obstacles.at(i)->rect())){
            qDebug() << "Objects collide";
            PhysicsUtils::moveToEdge(r,obstacles.at(i)->rect(),dir);
        }
    }
    player->rect->setRect(r);
}



SimpleCollisionView::~SimpleCollisionView(){

}
