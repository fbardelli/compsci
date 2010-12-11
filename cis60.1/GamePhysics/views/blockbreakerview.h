#ifndef BLOCKBREAKERVIEW_H
#define BLOCKBREAKERVIEW_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QGraphicsTextItem>
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
    QGraphicsTextItem * ballsField, * scoreField;
    bool rightPress, leftPress, ballInPlay;
    int blockCount, score, ballsRemaining;
    void handleCollision(Projectile * p, FixedRectangle *obstacle);
    void handleCollision(Projectile *p,  Paddle *obstacle);
    void handleCollision(Projectile * p, StandardBlock *obstacle);
    void setUpGameBoard();
    void setUpBlocks();
    void updateNumberField(QGraphicsTextItem *t, int num);
    void updateScore(int num);
    void updateBalls(int num);

public:
    BlockBreakerView(QGraphicsScene *scene,QWidget *parent);
    void winGame();
    void loseGame();
    void gameOver(QString message);
    const QString getInstructions();
    ~BlockBreakerView();
    void updateProjectiles();
protected:
   void keyPressEvent (QKeyEvent* e);
   void keyReleaseEvent (QKeyEvent* e);
signals:

public slots:
   void redraw();

};

#endif // BLOCKBREAKERVIEW_H
