#ifndef SPORTSCAR_H
#define SPORTSCAR_H

#include <QGraphicsPixmapItem>
#include <cmath>
#include <QDebug>
#include <QVector2D>

class SportsCar : public QGraphicsPixmapItem
{

private:
    int currentAngle;
    int speed;
    int topSpeed;
    bool canTurn;

public:
    explicit SportsCar(const QPixmap &pixmap, QGraphicsItem *parent = 0,
               QGraphicsScene *scene = 0);
    void accelerate();
    void reverse();
    void rightTurn(int degrees);
    void leftTurn(int degrees);
    void updatePosition();

};

#endif // SPORTSCAR_H
