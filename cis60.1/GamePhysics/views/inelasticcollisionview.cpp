#include "inelasticcollisionview.h"

InelasticCollisionView::InelasticCollisionView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    qDebug() << "x" << scene->width()/2 << "y" << scene->height();
    ball = new BouncyBall(scene->width()/2,scene->height()-50,this);
    //ball = new BouncyBall(0,0,this);

    scene->addItem(ball);
    text = scene->addText(getBouncinessReading(ball->getBounciness()));
    connect(ball, SIGNAL(bouncinessChanged(float)), this, SLOT(updateBounciness(float)));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer->start(50);
}

void InelasticCollisionView::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Up:
            ball->increaseBounciness();
            break;
        case Qt::Key_Down:
            ball->decreaseBounciness();
            break;
    }

}


QString InelasticCollisionView::getBouncinessReading(float b){
    QString result;
    QTextStream(&result) << "Bounciness: " << b;
    return result;
}

void InelasticCollisionView::updateBounciness(float b){
    text->setPlainText(getBouncinessReading(b));
}

void InelasticCollisionView::redraw(){
    ball->applyGravity();
    ball->updatePosition();
}

InelasticCollisionView::~InelasticCollisionView(){
    delete timer;
}

const QString InelasticCollisionView::getInstructions(){
    return QString(
        "This example models a collision between a ball and the ground."
        " You can increase the elasticity(bounciness) of the collision."
        " At 1.0 the collision is fully elastic, meaning no energy is lost when the"
        " ball hits the ground.  At lower levels energy is lost with each bounce."
        "<br/><table border='1' cellpadding='1' cellspacing='1'>"
            "<tr><th>Key</th><th>Action</th></tr>"
            "<tr><td>Left Mouse Click</td><td>Grab ball</td></tr>"
            "<tr><td>Left Mouse Release</td><td>Drop ball</td></tr>"
            "<tr><td>Up</td><td>Raise the elasticity of the ball</td></tr>"
            "<tr><td>Down</td><td>Lower the elasticity of the ball</td></tr>"
        "</table>"
    );

}
