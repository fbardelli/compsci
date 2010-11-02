#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QDebug>

class SpaceShip  : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
private:
    QGraphicsPixmapItem * ship;
    QGraphicsPixmapItem * leftThruster;
    QGraphicsPixmapItem * rightThruster;
    QGraphicsPixmapItem * bottomThruster;
    int angle, verticalSpeed, horizontalSpeed;
public:
    explicit SpaceShip(QGraphicsScene *scene);
    void fireMainThruster();
    void fireLeftThruster();
    void fireRightThruster();
    void cutMainThruster();
    void cutLeftThruster();
    void cutRightThruster();
    void updatePosition();

signals:

public slots:

};

#endif // SPACESHIP_H
