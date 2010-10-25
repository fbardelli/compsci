#ifndef GRAVITYVIEW_H
#define GRAVITYVIEW_H

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

class GravityView : public CommonView
{
Q_OBJECT

private:
    double gravity;
    QTimer *timer;
    JumpingMan *jumper;
    QGraphicsTextItem *text;
protected:
   void keyPressEvent (QKeyEvent* e);
public:
    GravityView(QGraphicsScene *scene,QWidget *parent);
    ~GravityView();
    const QString getInstructions();
    QString getGravityReading();
    void increaseGravity();
    void decreaseGravity();
signals:
    void gravityChanged();
private slots:
    void redraw();
    void detectLanding();
    void updateGravity();

};

#endif // GRAVITYVIEW_H
