#ifndef CANNON_H
#define CANNON_H

#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <sprites/projectile.h>

class Cannon : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
private:
    QGraphicsPixmapItem * cannonbarrel;
    QGraphicsPixmapItem * cannonbase;
    QList<Projectile *> projectiles;
    int angle;
    int projectileSpeed;
public:
    explicit Cannon(QGraphicsScene *scene);
    void incline();
    void decline();
    void fire();
    void updateProjectiles();
    void setProjectileSpeed(int speed);

signals:

public slots:

};

#endif // CANNON_H
