#ifndef JUMPINGMAN_H
#define JUMPINGMAN_H

#include <QGraphicsPixmapItem>

class JumpingMan : public QGraphicsPixmapItem
{
private:
    int horizontalSpeed;
    int verticalSpeed;
    bool jumping;
public:
    explicit JumpingMan(const QPixmap &pixmap, QGraphicsItem *parent = 0,
               QGraphicsScene *scene = 0);
    void moveForward();
    void moveBackward();
    int  getHorizonalSpeed();
    int  getVerticalSpeed();
    void stop();
    void applyGravity(int gravity);
    bool isJumping();
    void jump();
    void updatePosition();
};

#endif // JUMPINGMAN_H
