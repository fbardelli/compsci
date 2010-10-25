#include "simplecollisionview.h"

#define SQUARE_SIZE 50
#define MOVE_DISTANCE 10

SimpleCollisionView::SimpleCollisionView(QGraphicsScene *scene,QWidget *parent) :
        CommonView(scene,parent)
{
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
            MovableRectangle *obstacle;
            obstacle = new MovableRectangle(
                    scene->addRect(
                    QRectF(x, y, SQUARE_SIZE, SQUARE_SIZE),
                    QPen(QColor(Qt::black)),
                    QBrush(Qt::blue,Qt::SolidPattern)),
                    20,
                    0,
                    Right,
                    this);
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
    player->move(dir,obstacles);
}

const QString SimpleCollisionView::getInstructions(){
    return QString(
        "This is an example of simple collision detection"
        "The <b><font color='#ff0000'>Red</font></b> rectagle will not be able to pass through any of the "
        " <b><font color='#0000ff'>Blue</font></b> rectagles.  It will stop right at the edge of the obstacle and be forced to go around it."
        "<br/><table border='1' cellpadding='1' cellspacing='1'>"
            "<tr><th>Key</th><th>Action</th></tr>"
            "<tr><td>Up</td><td>Move <b><font color='#ff0000'>Red</font></b> rectangle toward the top of the screen</td></tr>"
            "<tr><td>Down</td><td>Move <b><font color='#ff0000'>Red</font></b> rectangle toward the bottom of the screen</td></tr>"
            "<tr><td>Left</td><td>Move <b><font color='#ff0000'>Red</font></b> rectangle toward the left of the screen</td></tr>"
            "<tr><td>Right</td><td>Move <b><font color='#ff0000'>Red</font></b> rectangle toward the right of the screen</td></tr>"
        "</table>"
    );

}


SimpleCollisionView::~SimpleCollisionView(){
    delete player;
    qDeleteAll(obstacles);
    obstacles.clear();
}
