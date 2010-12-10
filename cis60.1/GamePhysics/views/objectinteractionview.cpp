#include "objectinteractionview.h"

ObjectInteractionView::ObjectInteractionView(QGraphicsScene *scene,QWidget *parent):
        ProjectileView(scene,parent)
{
    //pyramid = new QList<StackableSphere *>();
    int bottom = scene->height() - 40;
    int xstart = 0; int xstop = 320;
    for(int h = 0; h <= 300; h += 40 ){
        //for(int i = xstart; i <= xstop; i +=40){
            StackableSphere * sphere = new StackableSphere();
            scene->addItem(sphere);
            //sphere->setPos(400+i,bottom-h);
            sphere->setPos(400,bottom-h);
            sphere->setPosition(QVector2D(sphere->pos()));
            pyramid.push_front(sphere);
        //}
        xstart+= 40;
        xstop -= 40;
    }
    connect(timer,SIGNAL(timeout()),this,SLOT(updatePyramid()));
    //wall = new FixedRectangle(700, -200, 50, scene->height()+400);
    //wall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    //wall->setPen(QPen(QColor(Qt::black)));
    //scene->addItem(wall);
}

void ObjectInteractionView::updatePyramid(){
    for (int i = 0; i < pyramid.size(); ++i) {
        StackableSphere *s = pyramid.at(i);
        s->setCollisionState(false);
        s->updatePosition();
    }
    for (int i = 0; i < pyramid.size(); ++i) {
        StackableSphere *s = pyramid.at(i);
        s->applyGravity();
    }
}

const QString ObjectInteractionView::getInstructions(){
    return QString(
        "This example simulates the reaction of moveable objects when hit by a projectile. "
        "<br/><table border='1' cellpadding='1' cellspacing='1'>"
            "<tr><th>Key</th><th>Action</th></tr>"
            "<tr><td>Up</td><td>Raise the angle of the cannon</td></tr>"
            "<tr><td>Down</td><td>Lower the angle of the cannon</td></tr>"
            "<tr><td>Space</td><td>Fire cannon</td></tr>"
        "</table>"
    );

}
