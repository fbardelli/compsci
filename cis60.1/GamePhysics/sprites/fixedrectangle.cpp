#include "fixedrectangle.h"

FixedRectangle::FixedRectangle(QObject *parent) :
    QObject(parent), QGraphicsRectItem()
{
}

/**
 Creates a new immoveable rectangle

 @param x x postion the FixedRectangle will start at
 @param y y postion the FixedRectangle will start at
 @param width Width of the FixedRectangle
 @param height Height of the FixedRectangle

*/
FixedRectangle::FixedRectangle( qreal x, qreal y, qreal width, qreal height, QObject * parent):
    QObject(parent), QGraphicsRectItem(x, y, width, height)
{

}



