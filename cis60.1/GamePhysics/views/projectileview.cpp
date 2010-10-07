#include "projectileview.h"

ProjectileView::ProjectileView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    cannon = new Cannon(scene);
    scene->addItem(cannon);
}

void ProjectileView::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Up:
            cannon->incline();
            break;
        case Qt::Key_Down:
            cannon->decline();
            break;
    }

}
