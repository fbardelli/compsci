#include "deflectionview.h"

DeflectionView::DeflectionView(QGraphicsScene *scene,QWidget *parent):
        ProjectileView(scene,parent)
{
    scene->addRect(
        QRectF(600, 0, 50, scene->height()),
        QPen(QColor(Qt::black)),
        QBrush(Qt::red,Qt::SolidPattern));
}
