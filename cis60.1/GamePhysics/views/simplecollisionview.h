#ifndef SIMPLECOLLISIONVIEW_H
#define SIMPLECOLLISIONVIEW_H

#include <QGraphicsView>
#include <QtGui/QGraphicsRectItem>
#include <QtAlgorithms>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "gameConstants.h"
#include "physicsutils.h"
#include "sprites/movablerectangle.h"
#include "views/commonview.h"

class SimpleCollisionView : public CommonView
{
private:
    MovableRectangle *player;
    QList<MovableRectangle *> obstacles;
    void moveToEdge(QRectF &p, QRectF o, Direction dir);
    bool objectsCollide(QRectF p, QRectF o);
public:
    SimpleCollisionView(QGraphicsScene *scene,QWidget *widget);
    ~SimpleCollisionView();
 protected:
    void keyPressEvent (QKeyEvent* e);
};

#endif // SIMPLECOLLISIONVIEW_H
