#include "gravityview.h"

GravityView::GravityView(QGraphicsScene *scene,QWidget *parent) :
        CommonView(scene,parent)
{
    QPixmap p = QPixmap(":faceguy.png");
    gravity = 1.0;
    jumper = new JumpingMan(p,scene);
    scene->addItem(jumper);
    text = scene->addText(getGravityReading());
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    connect(jumper, SIGNAL(landed()), this, SLOT(detectLanding()));
    connect(this,SIGNAL(gravityChanged()), this, SLOT(updateGravity()));
    timer->start(250);
}

void GravityView::detectLanding(){
    //text->setPlainText(getGravityReading());
}

QString GravityView::getGravityReading(){
    QString result;
    QTextStream(&result) << "Gravity " << gravity;
    return result;
}

void GravityView::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Space:
            jumper->jump();
            break;
        case Qt::Key_Left:
            jumper->moveBackward();
            break;
        case Qt::Key_Right:
            jumper->moveForward();
            break;
        case Qt::Key_Up:
            increaseGravity();
            break;
        case Qt::Key_Down:
            decreaseGravity();
            break;
    }

}

void GravityView::updateGravity(){
    text->setPlainText(getGravityReading());
}

void GravityView::increaseGravity(){
    if (gravity < 5.0)
        gravity += 0.25;
    emit gravityChanged();

}

void GravityView::decreaseGravity(){
    if (gravity > 0.25)
        gravity -= 0.25;
    emit gravityChanged();
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
