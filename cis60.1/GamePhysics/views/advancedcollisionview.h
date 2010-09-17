#ifndef ADVANCEDCOLLISIONVIEW_H
#define ADVANCEDCOLLISIONVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QTimer>
#include <qevent.h>
#include "gameConstants.h"
#include "sprites/movablerectangle.h"
#include "views/commonview.h"


class AdvancedCollisionView : public CommonView
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
