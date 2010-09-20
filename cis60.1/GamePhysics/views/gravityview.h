#ifndef GRAVITYVIEW_H
#define GRAVITYVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <qevent.h>
#include "gameConstants.h"
#include "sprites/movablerectangle.h"
#include "views/commonview.h"

class GravityView : public CommonView
{
Q_OBJECT

private:
    double gravity;
    QTimer *timer;
    MovableRectangle *player;
public:
    GravityView(QGraphicsScene *scene,QWidget *parent);

private slots:
    void redraw();

};

#endif // GRAVITYVIEW_H
