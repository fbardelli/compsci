#include "deflectionview.h"

DeflectionView::DeflectionView(QGraphicsScene *scene,QWidget *parent):
        ProjectileView(scene,parent)
{
    wall = new FixedRectangle(700, -200, 50, scene->height()+400);
    wall->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    wall->setPen(QPen(QColor(Qt::black)));
    scene->addItem(wall);
}
