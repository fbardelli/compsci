#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsView>
#include <QDebug>
#include <qevent.h>
#include <QList>
#include "views/commonview.h"
#include "views/simplecollisionview.h"
#include "views/advancedcollisionview.h"
#include "views/accelerateview.h"
#include "views/gravityview.h"
#include "views/projectileview.h"
#include "views/inelasticcollisionview.h"
#include "views/thrusterview.h"
#include "views/deflectionview.h"
#include "views/objectinteractionview.h"
#include "views/blockbreakerview.h"

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


private:
    Ui::GameMenu *ui;
    CommonView  *mainView;
    QGraphicsScene *scene;

};

#endif // GAMEMENU_H
