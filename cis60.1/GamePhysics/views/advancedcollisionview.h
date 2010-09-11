#ifndef ADVANCEDCOLLISIONVIEW_H
#define ADVANCEDCOLLISIONVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QTimer>
#include <qevent.h>
#include "gameConstants.h"
#include "simplecollisionview.h"
#include "sprites/movablerectangle.h"


class AdvancedCollisionView : public QGraphicsView
{

Q_OBJECT

private:
    MovableRectangle *player;
    QList<MovableRectangle *> obstacles;
    QTimer *timer;
public:
    AdvancedCollisionView(QGraphicsScene *scene,QWidget *parent);
    ~AdvancedCollisionView();
 protected:
    void keyPressEvent (QKeyEvent* e);
 private slots:
    void moveObstacles();
};

#endif // ADVANCEDCOLLISIONVIEW_H
