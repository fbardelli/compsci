#ifndef STANDARDBLOCK_H
#define STANDARDBLOCK_H

#include <QObject>
#include <QVector2D>
#include "sprites/blocks/blockbase.h"
class StandardBlock : public BlockBase
{
    Q_OBJECT
public:
    StandardBlock( qreal x, qreal y, qreal width, qreal height);
    // Enable the use of qgraphicsitem_cast with this item.
    enum { Type = UserType + 5 };
    int type() const {return Type;}
    void registerHit();
    void setBlockColor();
signals:

public slots:

};

#endif // STANDARDBLOCK_H
