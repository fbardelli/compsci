#ifndef ACCELERATEVIEW_H
#define ACCELERATEVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <qevent.h>
#include <QDebug>
#include <cmath>

class AccelerateView : public QGraphicsView
{

Q_OBJECT

private:
     QGraphicsPixmapItem * car;
     int currentAngle;
     int speed;
     bool canTurn;
public:
    AccelerateView(QGraphicsScene *scene,QWidget *parent);
    ~AccelerateView();
protected:
    void keyPressEvent (QKeyEvent* e);
private slots:
    void decelerate();
};

#endif // ACCELERATEVIEW_H
