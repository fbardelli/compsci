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
