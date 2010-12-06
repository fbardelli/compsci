#ifndef BLOCKBREAKERVIEW_H
#define BLOCKBREAKERVIEW_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include "sprites/blocks/paddle.h"
#include "sprites/projectile.h"
#include "views/commonview.h"

class BlockBreakerView: public CommonView
{
    Q_OBJECT
private:
    QTimer *timer;
    FixedRectangle * topWall;
    FixedRectangle * leftWall;
    FixedRectangle * rightWall;
    FixedRectangle * bottomWall;
    Paddle *paddle;
    Projectile *p;
    bool rightPress, leftPress;
    void handleCollision(Projectile * p,FixedRectangle *obstacle);
public:
    BlockBreakerView(QGraphicsScene *scene,QWidget *parent);
    ~BlockBreakerView();
    void updateProjectiles();
protected:
   void keyPressEvent (QKeyEvent* e);
   //void keyReleaseEvent (QKeyEvent* e);
signals:

public slots:
   void redraw();

};

#endif // BLOCKBREAKERVIEW_H
