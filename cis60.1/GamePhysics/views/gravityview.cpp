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
    connect(this, SIGNAL(gravityChanged()), this, SLOT(updateGravity()));
    timer->start(50);
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
const QString GravityView::getInstructions(){
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
GravityView::~GravityView(){
    delete timer;
}
