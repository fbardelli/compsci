#ifndef JUMPINGMAN_H
#define JUMPINGMAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QGraphicsScene>
class JumpingMan : public QObject, public QGraphicsPixmapItem {

Q_OBJECT

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
signals:
    void landed();
};

#endif // JUMPINGMAN_H
