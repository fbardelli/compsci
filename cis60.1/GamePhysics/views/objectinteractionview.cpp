#include "objectinteractionview.h"

ObjectInteractionView::ObjectInteractionView(QGraphicsScene *scene,QWidget *parent):
        ProjectileView(scene,parent)
{
    //pyramid = new QList<StackableSphere *>();
    int bottom = scene->height() - 42;
    int xstart = 0; int xstop = 320;
    for(int h = 0; h <= 280; h += 37 ){
        for(int i = xstart; i <= xstop; i +=42){
            StackableSphere * sphere = new StackableSphere();
            scene->addItem(sphere);
            sphere->setPos(400+i,bottom-h);
            //sphere->setVelocity(0.0,0.0);
            pyramid.append(sphere);
        }
        xstart+= 20;
        xstop -= 20;
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
        QVector2D position = QVector2D(s->pos().x(),s->pos().y());
        position += s->getVelocity();
        s->setPos(position.x(),position.y());
    }
}

/*

function resolveCollisionEqualMass (obj1, obj2, n)
   set u to obj1.velocity-obj2.velocity
   set un to componentVector(u,n)
   set ut to u-un
   set obj1.velocity to ut+obj2.velocity
   set obj2.velocity to un+obj2.velocity
end function
*/
