#include "advancedcollisionview.h"
#define SQUARE_SIZE 50
#define MOVE_DISTANCE 10

AdvancedCollisionView::AdvancedCollisionView(QGraphicsScene *scene,QWidget *parent)
{
    this->setParent(parent);
    this->setScene(scene);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,parent->width(),parent->height());
    player = scene->addRect(QRectF(0, 0, SQUARE_SIZE, SQUARE_SIZE),QPen(QColor(Qt::black)),QBrush(QColor(75,0,130,255),Qt::SolidPattern));
    QGraphicsRectItem *obstacleMovable, *obstacleStoppable, *obstacleUnstoppable;
    obstacleMovable = scene->addRect(QRectF(300, 50, SQUARE_SIZE, SQUARE_SIZE),QPen(QColor(Qt::black)),QBrush(QColor(0,255,0,150),Qt::SolidPattern));
    obstacles.push_back(obstacleMovable);
    obstacleStoppable = scene->addRect(QRectF(300, 200, SQUARE_SIZE, SQUARE_SIZE),QPen(QColor(Qt::black)),QBrush(QColor(255,255,0,200),Qt::SolidPattern));
    obstacles.push_back(obstacleStoppable);
    obstacleUnstoppable = scene->addRect(QRectF(300, 350, SQUARE_SIZE, SQUARE_SIZE),QPen(QColor(Qt::black)),QBrush(QColor(255,0,0,255),Qt::SolidPattern));
    obstacles.push_back(obstacleUnstoppable);

}
