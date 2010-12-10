#include "deflectionview.h"

DeflectionView::DeflectionView(QGraphicsScene *scene,QWidget *parent):
        ProjectileView(scene,parent)
{
    wall = new FixedRectangle(700, -200, 50, scene->height()+400);
    wall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    wall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(wall);
}

const QString DeflectionView::getInstructions(){
    return QString(
        "This example simulates the reaction a projectile as it slams into a fixed obstacle."
        "<br/><table border='1' cellpadding='1' cellspacing='1'>"
            "<tr><th>Key</th><th>Action</th></tr>"
            "<tr><td>Up</td><td>Raise the angle of the cannon</td></tr>"
            "<tr><td>Down</td><td>Lower the angle of the cannon</td></tr>"
            "<tr><td>Space</td><td>Fire cannon</td></tr>"
        "</table>"
    );

}
