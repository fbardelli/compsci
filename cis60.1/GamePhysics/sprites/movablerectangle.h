#ifndef MOVABLERECTANGLE_H
#define MOVABLERECTANGLE_H

#include <QObject>
#include <QtGui/QGraphicsRectItem>
#include <QGraphicsView>
#include "gameConstants.h"

class MovableRectangle : public QObject
{
public:
    int mass, velocity;
    QGraphicsRectItem *rect;
    QGraphicsView *world;
    Direction direction;
    MovableRectangle(QGraphicsRectItem *rect,int m, int v,Direction dir, QGraphicsView *world);
    QRectF move();
    QRectF move(Direction dir);
};

#endif // MOVABLERECTANGLE_H
