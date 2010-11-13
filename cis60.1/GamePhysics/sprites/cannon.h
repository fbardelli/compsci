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
public:
    explicit Cannon(QGraphicsScene *scene);
    void incline();
    void decline();
    void fire();
    void updateProjectiles();

signals:

public slots:

};

#endif // CANNON_H
