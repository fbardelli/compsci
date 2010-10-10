#include "projectileview.h"

ProjectileView::ProjectileView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    cannon = new Cannon(scene);
    scene->addItem(cannon);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer->start(250);
}

void ProjectileView::redraw(){
    cannon->updateProjectiles();
}

void ProjectileView::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Up:
            cannon->incline();
            break;
        case Qt::Key_Down:
            cannon->decline();
            break;
        case Qt::Key_Space:
            cannon->fire();
            break;
    }

}
