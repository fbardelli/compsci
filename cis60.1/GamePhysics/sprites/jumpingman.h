#ifndef JUMPINGMAN_H
#define JUMPINGMAN_H

#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QGraphicsScene>
class JumpingMan : public QGraphicsPixmapItem
{
private:
    int horizontalSpeed;
    int verticalSpeed;
    bool jumping, facingRight;
public:
    explicit JumpingMan(const QPixmap &pixmap,
               QGraphicsScene *scene);
    void moveForward();
    void moveBackward();
    int  getHorizonalSpeed();
    int  getVerticalSpeed();
    void stop();
    void applyGravity(double gravity);
    bool isJumping();
    void jump();
    void updatePosition();
};

#endif // JUMPINGMAN_H
