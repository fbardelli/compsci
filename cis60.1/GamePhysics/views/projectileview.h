#ifndef PROJECTILEVIEW_H
#define PROJECTILEVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "gameConstants.h"
#include "views/commonview.h"

class ProjectileView : public CommonView
{
Q_OBJECT

public:
    ProjectileView(QGraphicsScene *scene,QWidget *parent);

signals:

public slots:

};

#endif // PROJECTILEVIEW_H
