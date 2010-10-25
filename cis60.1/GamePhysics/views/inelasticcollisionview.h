#ifndef INELASTICCOLLISIONVIEW_H
#define INELASTICCOLLISIONVIEW_H

#include "views/commonview.h"
#include "sprites/bouncyball.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QEvent>
#include <QKeyEvent>

class InelasticCollisionView : public CommonView
{
Q_OBJECT

private:
    BouncyBall * ball;
    QTimer * timer;
    QGraphicsTextItem *text;
    QString getBouncinessReading(float b);
public:
    InelasticCollisionView(QGraphicsScene *scene,QWidget *parent);
    ~InelasticCollisionView();
protected:
    void keyPressEvent(QKeyEvent *e);
private slots:
    void redraw();
    void updateBounciness(float b);
};

#endif // INELASTICCOLLISIONVIEW_H
