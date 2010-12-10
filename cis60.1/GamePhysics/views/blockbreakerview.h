#ifndef BLOCKBREAKERVIEW_H
#define BLOCKBREAKERVIEW_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include "sprites/blocks/paddle.h"
#include "sprites/projectile.h"
#include "sprites/blocks/standardblock.h"
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
    Projectile *projectile;
    bool rightPress, leftPress, ballInPlay;
    void handleCollision(Projectile * p, FixedRectangle *obstacle);
    void handleCollision(Projectile *p,  Paddle *obstacle);
    void handleCollision(Projectile * p, StandardBlock *obstacle);
public:
    BlockBreakerView(QGraphicsScene *scene,QWidget *parent);
    const QString getInstructions();
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
