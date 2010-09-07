#ifndef ACCELERATEVIEW_H
#define ACCELERATEVIEW_H

#include <QGraphicsView>

class AccelerateView : public QGraphicsView
{
public:
    AccelerateView(QGraphicsScene *scene,QWidget *parent);
    ~AccelerateView();
};

#endif // ACCELERATEVIEW_H
