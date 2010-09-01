#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsRectItem>
#include <QDebug>
#include <qevent.h>

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
    bool objectsCollide(QRectF p, QRectF o);

private slots:
    void runSimulation();
    //void moveRect();
    //void handleKeyPress(QKeyEvent& e);

//signals:
    //void key_pressed(QKeyEvent& e);

 protected:
    void keyPressEvent (QKeyEvent* e);


private:
    Ui::GameMenu *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *player;
    QGraphicsRectItem *obstacle;
};

#endif // GAMEMENU_H
