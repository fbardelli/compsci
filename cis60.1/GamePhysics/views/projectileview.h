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
#include "sprites/projectile.h"

class ProjectileView : public CommonView
{
Q_OBJECT
private:
    Cannon *cannon;
protected:
   void keyPressEvent (QKeyEvent* e);
    QTimer *timer;
public:
    ProjectileView(QGraphicsScene *scene,QWidget *parent);
    ~ProjectileView();
    const QString getInstructions();
    void cleanupProjectiles();
signals:

public slots:
    void redraw();

};

#endif // PROJECTILEVIEW_H
