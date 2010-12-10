#ifndef BLOCKBASE_H
#define BLOCKBASE_H

#include <QObject>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QVector2D>
#include <QGraphicsRectItem>


class BlockBase : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int points;
    int health;
public:
    BlockBase( qreal x, qreal y, qreal width, qreal height, QObject * parent = 0);
    enum { Type = UserType + 4 };
    int type() const {return Type;}
    int getHealth(){ return health; }
    int getPoints(){ return points; }
    void setPoints(int p){ points = p;}
    void setHealth(int h){ health = h;}
signals:

public slots:

};

#endif // BLOCKBASE_H
