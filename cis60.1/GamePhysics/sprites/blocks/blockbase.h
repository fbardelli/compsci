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

signals:

public slots:

};

#endif // BLOCKBASE_H
