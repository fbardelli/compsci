#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QtGui/QMainWindow>

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

private:
    Ui::GameMenu *ui;
};

#endif // GAMEMENU_H
