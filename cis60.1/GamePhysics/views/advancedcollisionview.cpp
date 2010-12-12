#include "advancedcollisionview.h"
#define SQUARE_SIZE 50
#define MOVE_DISTANCE 10

AdvancedCollisionView::AdvancedCollisionView(QGraphicsScene *scene,QWidget *parent) :
        CommonView(scene,parent)
{
    player = new MovableRectangle(
                scene->addRect(
                    QRectF(0, 0, SQUARE_SIZE, SQUARE_SIZE),
                    QPen(QColor(Qt::black)),
                    QBrush(QColor(75,0,130,255),Qt::SolidPattern)),
                10,
                MOVE_DISTANCE,
                Left,
                this);
    obstacles.push_back(player);
    MovableRectangle *obstacleMovable, *obstacleStoppable, *obstacleUnstoppable;
    obstacleMovable = new MovableRectangle(
            scene->addRect(
                QRectF(300, 60, SQUARE_SIZE, SQUARE_SIZE),
                QPen(QColor(Qt::black)),
                QBrush(QColor(0,255,0,150),Qt::SolidPattern)),
                5,
                20,
                Right,
                this);
    obstacles.push_back(obstacleMovable);
    obstacleStoppable = new MovableRectangle(
            scene->addRect(
                QRectF(300, 210, SQUARE_SIZE, SQUARE_SIZE),
                QPen(QColor(Qt::black)),
                QBrush(QColor(255,255,0,200),Qt::SolidPattern)),
            10,
            5,
            Right,
            this);
    obstacles.push_back(obstacleStoppable);
    obstacleUnstoppable = new MovableRectangle(
            scene->addRect(
                QRectF(300, 360, SQUARE_SIZE, SQUARE_SIZE),
                QPen(QColor(Qt::black)),
                QBrush(QColor(255,0,0,255),Qt::SolidPattern)),
            20,
            10,
            Right,
            this);
    obstacles.push_back(obstacleUnstoppable);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveObstacles()));
    timer->start(125);
}


void AdvancedCollisionView::moveObstacles(){
    for (int i = 0; i < obstacles.size(); ++i) {
        MovableRectangle *ob = obstacles.at(i);
        if(ob != player)
            ob->move(obstacles);
    }
}


void AdvancedCollisionView::keyPressEvent(QKeyEvent *e){
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
    player->move(dir,obstacles);
}



AdvancedCollisionView::~AdvancedCollisionView(){
    qDeleteAll(obstacles);
    obstacles.clear();
    delete timer;
}


const QString AdvancedCollisionView::getInstructions(){
    return QString(
        "These moving rectangles react differently to the <b><font color='#4b0082'>Purple</font></b> rectangle. "
        "The <b><font color='#00ff00'>Green</font></b> rectagle can be pushed by the <b><font color='#4b0082'>Purple</font></b> one."
        "The <b><font color='#ffff00'>Yellow</font></b> rectagle can not push or be pushed by the <b><font color='#4b0082'>Purple</font></b> one."
        "The <b><font color='#ff0000'>Red</font></b> rectagle can push the <b><font color='#4b0082'>Purple</font></b> one."
        "<br/><table border='1' cellpadding='1' cellspacing='1'>"
            "<tr><th>Key</th><th>Action</th></tr>"
            "<tr><td>Up</td><td>Move <b><font color='#4b0082'>Purple</font></b> rectangle toward the top of the screen</td></tr>"
            "<tr><td>Down</td><td>Move <b><font color='#4b0082'>Purple</font></b> rectangle toward the bottom of the screen</td></tr>"
            "<tr><td>Left</td><td>Move <b><font color='#4b0082'>Purple</font></b> rectangle toward the left of the screen</td></tr>"
            "<tr><td>Right</td><td>Move <b><font color='#4b0082'>Purple</font></b> rectangle toward the right of the screen</td></tr>"
        "</table>"
    );

}
