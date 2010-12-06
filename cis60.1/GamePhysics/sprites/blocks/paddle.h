#ifndef PADDLE_H
#define PADDLE_H
#include <QObject>
#include <QVector2D>
#include "sprites/blocks/blockbase.h"
#include "sprites/projectile.h"

class Paddle : public BlockBase
{
    Q_OBJECT
public:
    Paddle( qreal x, qreal y, qreal width, qreal height);
    Projectile * launchBall();
signals:

public slots:

};

#endif // PADDLE_H
