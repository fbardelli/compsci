#ifndef THRUSTERVIEW_H
#define THRUSTERVIEW_H


#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "gameConstants.h"
#include "sprites/movablerectangle.h"
#include "sprites/jumpingman.h"
#include "views/commonview.h"

class ThrusterView : public CommonView
{
Q_OBJECT

private:
    double gravity;
    QTimer *timer;
    //SpaceShip *spaceship;
    QGraphicsTextItem *text;
protected:
   void keyPressEvent (QKeyEvent* e);
public:
    ThrusterView(QGraphicsScene *scene,QWidget *parent);
    ~ThrusterView();
    const QString getInstructions();
signals:
private slots:
    void redraw();

};

#endif // THRUSTERVIEW_H

