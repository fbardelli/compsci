#ifndef CANNON_H
#define CANNON_H

#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class Cannon : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
private:
    QGraphicsPixmapItem * cannonbarrel;
    QGraphicsPixmapItem * cannonbase;
public:
    explicit Cannon(QGraphicsScene *scene);
    void incline();
    void decline();

signals:

public slots:

};

#endif // CANNON_H
