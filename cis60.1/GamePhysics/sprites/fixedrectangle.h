#ifndef FIXEDRECTANGLE_H
#define FIXEDRECTANGLE_H

#include <QGraphicsRectItem>

class FixedRectangle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    FixedRectangle(QObject *parent = 0);
    FixedRectangle( qreal x, qreal y, qreal width, qreal height, QObject * parent = 0 );
    // Enable the use of qgraphicsitem_cast with this item.
    enum { Type = UserType + 1 };
    int type() const {return Type;}


signals:

public slots:

};

#endif // FIXEDRECTANGLE_H
