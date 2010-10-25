#ifndef PROJECTILEVIEW_H
#define PROJECTILEVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QTimer>
#include "gameConstants.h"
#include "views/commonview.h"
#include "sprites/cannon.h"
#include "sprites/projectile.h"

class ProjectileView : public CommonView
{
Q_OBJECT
private:
    Cannon *cannon;
    QTimer *timer;
protected:
   void keyPressEvent (QKeyEvent* e);
public:
    ProjectileView(QGraphicsScene *scene,QWidget *parent);
    ~ProjectileView();
    const QString getInstructions();

signals:

public slots:
    void redraw();

};

#endif // PROJECTILEVIEW_H
