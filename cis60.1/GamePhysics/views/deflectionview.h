#ifndef DEFLECTIONVIEW_H
#define DEFLECTIONVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "views/projectileview.h"
#include "sprites/fixedrectangle.h"

class DeflectionView : public ProjectileView
{
    Q_OBJECT
private:
    FixedRectangle * wall;
public:
    DeflectionView(QGraphicsScene *scene,QWidget *parent);
    const QString getInstructions();
signals:

public slots:

};

#endif // DEFLECTIONVIEW_H
