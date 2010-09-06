#ifndef MOVABLERECTANGLE_H
#define MOVABLERECTANGLE_H

#include <QObject>
#include <QtGui/QGraphicsRectItem>
#include <QGraphicsView>
#include <QDebug>
#include "physicsutils.h"
#include "gameConstants.h"

class MovableRectangle : public QObject
{
private:
    QRectF _moveRect(Direction dir);
public:
    int mass, velocity;
    QGraphicsRectItem *rect;
    QGraphicsView *world;
    Direction direction;
    MovableRectangle(QGraphicsRectItem *rect,int m, int v,Direction dir, QGraphicsView *world);
    void move();
    void move(Direction dir);
    void move(Direction dir,QList<MovableRectangle *> obstacles);
};

#endif // MOVABLERECTANGLE_H
