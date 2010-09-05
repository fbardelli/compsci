#ifndef ADVANCEDCOLLISIONVIEW_H
#define ADVANCEDCOLLISIONVIEW_H

#include <QGraphicsView>
#include "gameConstants.h"
#include "simplecollisionview.h"


class AdvancedCollisionView : public QGraphicsView
{
private:
    QGraphicsRectItem *player;
    QList<QGraphicsRectItem *> obstacles;
public:
    AdvancedCollisionView(QGraphicsScene *scene,QWidget *parent);
};

#endif // ADVANCEDCOLLISIONVIEW_H
