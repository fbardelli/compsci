#include "gravityview.h"

GravityView::GravityView(QGraphicsScene *scene,QWidget *parent) :
        CommonView(scene,parent)
{
    QPixmap p = QPixmap(":faceguy.png");
    jumper = new JumpingMan(p);
    scene->addItem(jumper);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer->start(250);
}

void GravityView::redraw(){

}
