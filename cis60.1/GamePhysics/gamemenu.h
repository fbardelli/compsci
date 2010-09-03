#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsView>
#include <QDebug>
#include <qevent.h>
#include <QList>

enum Direction { Right, Left, Up, Down };

namespace Ui
{
    class GameMenu;
}

class GameMenu : public QMainWindow
{
    Q_OBJECT

public:
    GameMenu(QWidget *parent = 0);
    ~GameMenu();
    void moveToEdge(QRectF &p, QRectF o, Direction dir);
    bool objectsCollide(QRectF p, QRectF o);

private slots:
    void runSimulation();

//signals:
    //void key_pressed(QKeyEvent& e);

 protected:
    void keyPressEvent (QKeyEvent* e);


private:
    Ui::GameMenu *ui;
    QGraphicsView  *mainView;
    QGraphicsScene *scene;
    QGraphicsRectItem *player;
    QList<QGraphicsRectItem *> obstacles;
};

#endif // GAMEMENU_H
