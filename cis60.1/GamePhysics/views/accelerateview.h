#ifndef ACCELERATEVIEW_H
#define ACCELERATEVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include "sprites/sportscar.h"
#include "views/commonview.h"

class AccelerateView : public CommonView
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
