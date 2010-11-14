#include "fixedrectangle.h"

FixedRectangle::FixedRectangle(QObject *parent) :
    QObject(parent), QGraphicsRectItem()
{
}

FixedRectangle::FixedRectangle( qreal x, qreal y, qreal width, qreal height, QObject * parent):
    QObject(parent), QGraphicsRectItem(x, y, width, height)
{

}



