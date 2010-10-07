#ifndef PROJECTILEVIEW_H
#define PROJECTILEVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "gameConstants.h"
#include "views/commonview.h"
#include "sprites/cannon.h"

class ProjectileView : public CommonView
{
Q_OBJECT
private:
    Cannon * cannon;
protected:
   void keyPressEvent (QKeyEvent* e);
public:
    ProjectileView(QGraphicsScene *scene,QWidget *parent);

signals:

public slots:

};

#endif // PROJECTILEVIEW_H
