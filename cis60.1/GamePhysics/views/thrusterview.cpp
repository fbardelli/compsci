#include "thrusterview.h"

ThrusterView::ThrusterView(QGraphicsScene *scene,QWidget *parent) :
        CommonView(scene,parent)
{
    spaceship = new SpaceShip(scene);
    gravity = 1.0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    upPress = leftPress = rightPress = false;
    timer->start(50);
}


void ThrusterView::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Up:
            upPress = true;
            break;
        case Qt::Key_Left:
            leftPress = true;
            break;
        case Qt::Key_Right:
            rightPress = true;
            break;
    }

}

void ThrusterView::keyReleaseEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Up:
            upPress = false;
            break;
        case Qt::Key_Left:
            leftPress = false;
            break;
        case Qt::Key_Right:
            rightPress = false;
            break;
    }

}

void ThrusterView::redraw(){
    if(leftPress){
        spaceship->fireLeftThruster();
    }else{
        spaceship->cutLeftThruster();
    }
    if(rightPress){
        spaceship->fireRightThruster();
    }else{
        spaceship->cutRightThruster();
    }
    if(upPress){
        spaceship->fireMainThruster();
    }else{
        spaceship->cutMainThruster();
    }
    spaceship->updatePosition();
}

const QString ThrusterView::getInstructions(){
    return QString(
        "This example simulates the effect of lift weight and thrust. "
        " The bottom lifter overcomes the spaceship's own weight and the forces of gravity."
        " The right and left thrusters tilt the ship and counteract drag, moving the ship right or left"
        "<br/><table border='1' cellpadding='1' cellspacing='1'>"
            "<tr><th>Key</th><th>Action</th></tr>"
            "<tr><td>Up</td><td>Fire the bottom rocket</td></tr>"
            "<tr><td>Left</td><td>Fire the left thrusters</td></tr>"
            "<tr><td>Right</td><td>Fire the right thrusters</td></tr>"
        "</table>"
    );

}

ThrusterView::~ThrusterView(){
    delete timer;
}

