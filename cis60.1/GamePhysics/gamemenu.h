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
    QGraphicsRectItem *rect;
};

#endif // GAMEMENU_H
