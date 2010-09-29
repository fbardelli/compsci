#include "gravityview.h"

GravityView::GravityView(QGraphicsScene *scene,QWidget *parent) :
        CommonView(scene,parent)
{
    QPixmap p = QPixmap(":faceguy.png");
    gravity = 1.0;
    jumper = new JumpingMan(p,scene);
    scene->addItem(jumper);
    text = scene->addText("Gravity: 1.0");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    connect(jumper, SIGNAL(landed()), this, SLOT(detectLanding()));
    timer->start(250);
}

void GravityView::detectLanding(){
    text->setPlainText("LANDED");
}

void GravityView::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Space:
            jumper->jump();
            text->setPlainText("JUUUUUUMP");
            break;
        case Qt::Key_Left:
            jumper->moveBackward();
            break;
        case Qt::Key_Right:
            jumper->moveForward();
            break;
    }

}

void GravityView::redraw(){
    jumper->applyGravity(gravity);
    jumper->updatePosition();
    if(! jumper->isJumping()){
        jumper->stop();
    }

}

GravityView::~GravityView(){
    //delete jumper;
    delete timer;
}
