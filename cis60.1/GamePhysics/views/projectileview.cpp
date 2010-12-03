#include "projectileview.h"

ProjectileView::ProjectileView(QGraphicsScene *scene,QWidget *parent):
        CommonView(scene,parent)
{
    cannon = new Cannon(scene);
    scene->addItem(cannon);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer->start(125);
}

void ProjectileView::redraw(){
    cannon->updateProjectiles();
    this->cleanupProjectiles();
}

void ProjectileView::cleanupProjectiles(){
    QList<QGraphicsItem *> sceneItems = this->scene()->items();
    if(sceneItems.size() > 0){
        //remove items that fall below the bottom of the screen
        //this greatly improves performance
        for (int i = 0; i < sceneItems.size(); ++i) {
            QGraphicsItem *p = sceneItems.at(i);
            if(p->y() > this->scene()->height()+100){
                //qDebug() << "removing junk";
                this->scene()->removeItem(p);
            }
        }
    }
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

const QString ProjectileView::getInstructions(){
    return QString(
        "This example simulates the path of a projectile fired from a cannon. "
        "<br/><table border='1' cellpadding='1' cellspacing='1'>"
            "<tr><th>Key</th><th>Action</th></tr>"
            "<tr><td>Up</td><td>Raise the angle of the cannon</td></tr>"
            "<tr><td>Down</td><td>Lower the angle of the cannon</td></tr>"
            "<tr><td>Space</td><td>Fire cannon</td></tr>"
        "</table>"
    );

}

ProjectileView::~ProjectileView(){
    delete timer;
}
