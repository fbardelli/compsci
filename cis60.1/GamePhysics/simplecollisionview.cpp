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
    player = scene->addRect(QRectF(0, 0, SQUARE_SIZE, SQUARE_SIZE),QPen(QColor(Qt::black)),QBrush(Qt::red,Qt::SolidPattern));
    for (int x = 75; x < parent->width(); x += 150) {
        for(int y = 0; y < parent->height(); y+= 150) {
            QGraphicsRectItem *obstacle;
            obstacle = scene->addRect(QRectF(x, y, SQUARE_SIZE, SQUARE_SIZE),QPen(QColor(Qt::black)),QBrush(Qt::blue,Qt::SolidPattern));
            obstacles.push_back(obstacle);
        }

    }
}


void SimpleCollisionView::keyPressEvent(QKeyEvent *e){
    QRectF r = player->rect();
    int boardWidth  = this->width();
    int boardHeight = this->height();
    Direction dir;
    switch(e->key()){
        case Qt::Key_Up:
            dir = Up;
            r.moveTo(r.x(),r.y()-MOVE_DISTANCE);
            if(r.y() < 0){
                r.moveTo(r.x(),0);
            }
            break;
        case Qt::Key_Down:
            dir = Down;
            r.moveTo(r.x(),r.y()+MOVE_DISTANCE);
            if( (r.y() + SQUARE_SIZE) > boardHeight){
                r.moveTo(r.x(),boardHeight-SQUARE_SIZE-1);
            }
            break;
        case Qt::Key_Left:
            dir = Left;
            r.moveTo(r.x()-MOVE_DISTANCE,r.y());
            if(r.x()-MOVE_DISTANCE < 0){
                r.moveTo(0,r.y());
            }
            break;
        case Qt::Key_Right:
            dir = Right;
            r.moveTo(r.x()+MOVE_DISTANCE,r.y());
            if( (r.x() + SQUARE_SIZE) > boardWidth){
                r.moveTo(boardWidth - SQUARE_SIZE-1,r.y());
            }
            break;
    }

    for (int i = 0; i < obstacles.size(); ++i) {
        if(objectsCollide(r,obstacles.at(i)->rect())){
            qDebug() << "Objects collide";
            moveToEdge(r,obstacles.at(i)->rect(),dir);
        }
    }
    player->setRect(r);
}

void SimpleCollisionView::moveToEdge(QRectF &p, QRectF o, Direction dir){
    if(dir == Right){
        //qDebug() << "px:" << p.x() << " ox:" << o.x() << " pw:" << p.width() << " ow:" << o.width();
        p.moveTo( (o.x()-SQUARE_SIZE-1),p.y());
    }else if (dir == Left){
        p.moveTo(o.x()+SQUARE_SIZE+1,p.y());
    }else if (dir == Down){
        p.moveTo(p.x(), (o.y()-SQUARE_SIZE-1) );
    }else if (dir == Up){
        p.moveTo(p.x(),o.y()+SQUARE_SIZE+1);
    }

}

bool SimpleCollisionView::objectsCollide(QRectF p, QRectF o){
    int pLeft = p.x();
    int oLeft = o.x();
    int pRight = p.x() + SQUARE_SIZE;
    int oRight = o.x() + SQUARE_SIZE;
    int pTop   = p.y();
    int oTop   = o.y();
    int pBottom = p.y() + SQUARE_SIZE;
    int oBottom = o.y() + SQUARE_SIZE;
    // is player fully above obstacle?
    if (pBottom < oTop) return false;
    // is player fully below obstacle?
    if (pTop > oBottom) return false;
    //Is player to the right of obstacle?
    if (pRight < oLeft) return false;
    //Is player to the left of obstacle?
    if (pLeft > oRight) return false;
    //otherwise player collides with obstacle.
    return true;
}

SimpleCollisionView::~SimpleCollisionView(){

}
