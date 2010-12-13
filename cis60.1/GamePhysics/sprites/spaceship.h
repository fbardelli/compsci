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
    QGraphicsPixmapItem * mainThruster;
    int angle, verticalSpeed, horizontalSpeed;
    bool mainThrusterOn, rightThrusterOn, leftThrusterOn;
    QPointF getNextPosition(QPointF point);

public:
    explicit SpaceShip(QGraphicsScene *scene);
    void fireMainThruster();
    void fireLeftThruster();
    void fireRightThruster();
    void cutMainThruster();
    void cutLeftThruster();
    void cutRightThruster();
    void levelSpaceship();
    void updatePosition();
    void applyDrag();
signals:

public slots:

};

#endif // SPACESHIP_H
