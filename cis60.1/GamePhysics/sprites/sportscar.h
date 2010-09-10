#ifndef SPORTSCAR_H
#define SPORTSCAR_H

#include <QGraphicsPixmapItem>
#include <cmath>

class SportsCar : public QGraphicsPixmapItem
{


private:
    int currentAngle;
    int speed;
    int topSpeed;
    bool canTurn;

public:
    explicit SportsCar( QGraphicsItem  * parent = 0, QGraphicsScene  * scene = 0);
    void accelerate();
    void reverse();
    void rightTurn(int degrees);
    void leftTurn(int degrees);
    void redraw();

};

#endif // SPORTSCAR_H
