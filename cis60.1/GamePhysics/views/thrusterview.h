#ifndef THRUSTERVIEW_H
#define THRUSTERVIEW_H


#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "gameConstants.h"
#include "views/commonview.h"
#include "sprites/spaceship.h"

class ThrusterView : public CommonView
{
Q_OBJECT

private:
    double gravity;
    QTimer *timer;
    SpaceShip *spaceship;
    bool upPress, rightPress, leftPress;
protected:
   void keyPressEvent (QKeyEvent* e);
   void keyReleaseEvent (QKeyEvent* e);
public:
    ThrusterView(QGraphicsScene *scene,QWidget *parent);
    ~ThrusterView();
    const QString getInstructions();
signals:
private slots:
    void redraw();

};

#endif // THRUSTERVIEW_H

