#ifndef SIMPLECOLLISIONVIEW_H
#define SIMPLECOLLISIONVIEW_H

#include <QGraphicsView>
#include <QtGui/QGraphicsRectItem>
#include <QtAlgorithms>
#include <QDebug>
#include <qevent.h>
#include "physicsutils.h"

enum Direction { Right, Left, Up, Down };

class SimpleCollisionView : public QGraphicsView
{
private:
    QGraphicsRectItem *player;
    QList<QGraphicsRectItem *> obstacles;
    void moveToEdge(QRectF &p, QRectF o, Direction dir);
    bool objectsCollide(QRectF p, QRectF o);
public:
    SimpleCollisionView(QGraphicsScene *scene,QWidget *widget);
    ~SimpleCollisionView();
 protected:
    void keyPressEvent (QKeyEvent* e);
};

#endif // SIMPLECOLLISIONVIEW_H