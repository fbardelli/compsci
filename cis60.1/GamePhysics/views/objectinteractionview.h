#ifndef OBJECTINTERACTIONVIEW_H
#define OBJECTINTERACTIONVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "views/projectileview.h"
#include "sprites/stackablesphere.h"

class ObjectInteractionView : public ProjectileView
{
    Q_OBJECT
private:
    QList<StackableSphere *> pyramid;
public:
    ObjectInteractionView(QGraphicsScene *scene,QWidget *parent);

signals:

public slots:
    void updatePyramid();

};

#endif // OBJECTINTERACTIONVIEW_H
