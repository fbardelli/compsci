#ifndef ACCELERATEVIEW_H
#define ACCELERATEVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <qevent.h>
#include <QDebug>
#include <sprites/sportscar.h>

class AccelerateView : public QGraphicsView
{

Q_OBJECT

private:
     SportsCar * car;
     QTimer    * timer;

public:
    AccelerateView(QGraphicsScene *scene,QWidget *parent);
    ~AccelerateView();
protected:
    void keyPressEvent (QKeyEvent* e);
public slots:
    void redraw();
};

#endif // ACCELERATEVIEW_H
