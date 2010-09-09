#ifndef ACCELERATEVIEW_H
#define ACCELERATEVIEW_H

#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <qevent.h>
#include <QDebug>
#include <cmath>

class AccelerateView : public QGraphicsView
{
private:
     QGraphicsPixmapItem * car;
     int currentAngle;
public:
    AccelerateView(QGraphicsScene *scene,QWidget *parent);
    ~AccelerateView();
 protected:
    void keyPressEvent (QKeyEvent* e);
};

#endif // ACCELERATEVIEW_H
