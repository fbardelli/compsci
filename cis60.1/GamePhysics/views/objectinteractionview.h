#ifndef OBJECTINTERACTIONVIEW_H
#define OBJECTINTERACTIONVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "views/projectileview.h"

class ObjectInteractionView : public ProjectileView
{
    Q_OBJECT
private:
public:
    ObjectInteractionView(QGraphicsScene *scene,QWidget *parent);

signals:

public slots:

};

#endif // OBJECTINTERACTIONVIEW_H
