#ifndef DEFLECTIONVIEW_H
#define DEFLECTIONVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "views/projectileview.h"

class DeflectionView : public ProjectileView
{
    Q_OBJECT
public:
    DeflectionView(QGraphicsScene *scene,QWidget *parent);

signals:

public slots:

};

#endif // DEFLECTIONVIEW_H
