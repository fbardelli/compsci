#ifndef BOUNCYBALL_H
#define BOUNCYBALL_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QLinearGradient>
#include <QApplication>
#include <QGradient>
#include <QPainter>
#include <QCursor>
#include <QPen>
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsSceneMouseEvent>

class BouncyBall : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
private:
    QGraphicsView *world;
    bool dragged;
    int verticalSpeed;
    float bounciness;

public:
    BouncyBall(int x, int y, QGraphicsView *w);
    int getVerticalSpeed();
    void applyGravity();
    void updatePosition();
    float getBounciness();
    void increaseBounciness();
    void decreaseBounciness();

protected:
    /*
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void bouncinessChanged(float b);

};

#endif // BOUNCYBALL_H
