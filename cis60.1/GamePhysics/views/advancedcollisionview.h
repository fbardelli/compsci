#ifndef ADVANCEDCOLLISIONVIEW_H
#define ADVANCEDCOLLISIONVIEW_H

#include <QGraphicsView>
#include <qevent.h>
#include "gameConstants.h"
#include "simplecollisionview.h"
#include "sprites/movablerectangle.h"ß


class AdvancedCollisionView : public QGraphicsView
{
private:
    MovableRectangle *player;
    QList<QGraphicsRectItem *> obstacles;
public:
    AdvancedCollisionView(QGraphicsScene *scene,QWidget *parent);
    ~AdvancedCollisionView();
 protected:
    void keyPressEvent (QKeyEvent* e);
};

#endif // ADVANCEDCOLLISIONVIEW_H
