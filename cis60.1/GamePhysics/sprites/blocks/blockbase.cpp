#include "blockbase.h"


 BlockBase::BlockBase( qreal x, qreal y, qreal width, qreal height, QObject * parent):
    QObject(parent), QGraphicsRectItem(x, y, width, height)
{
    //this->setPos(x,y);
    this->setRect(0,0,width,height);
    this->setPos(x,y);
}
