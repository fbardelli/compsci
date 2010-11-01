#include "thrusterview.h"

ThrusterView::ThrusterView(QGraphicsScene *scene,QWidget *parent) :
        CommonView(scene,parent)
{
    gravity = 1.0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer->start(50);
}


void ThrusterView::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Left:
            //spaceship->leftThruster();
            break;
        case Qt::Key_Right:
            //spaceship->rightThruster();
            break;
        case Qt::Key_Up:
            //spaceship->mainThruster();
            break;
        case Qt::Key_Down:
            //
            break;
    }

}


void ThrusterView::redraw(){
    //spaceship->applyGravity(gravity);
    //spaceship->updatePosition();
}

const QString ThrusterView::getInstructions(){
    return QString(
        "This example simulates the effect of gravity on a jumping character. "
        "If you lower the gravity constant displayed, the jumper will rise higher and fall slower. "
        "If you raise the gravity, the jumper will not rise very high and will fall rapidly."
        "<br/><table border='1' cellpadding='1' cellspacing='1'>"
            "<tr><th>Key</th><th>Action</th></tr>"
            "<tr><td>Up</td><td>Raise the gravity constant displayed at the top of the screen</td></tr>"
            "<tr><td>Down</td><td>Lower the gravity constant displayed at the top of the screen</td></tr>"
            "<tr><td>Left</td><td>Move character toward the left of the screen</td></tr>"
            "<tr><td>Right</td><td>Move character toward the right of the screen</td></tr>"
            "<tr><td>Space</td><td>Make character jump in the air</td></tr>"
        "</table>"
    );

}

ThrusterView::~ThrusterView(){
    delete timer;
}

