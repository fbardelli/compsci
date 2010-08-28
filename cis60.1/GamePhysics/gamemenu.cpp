#include "gamemenu.h"
#include "ui_gamemenu.h"

GameMenu::GameMenu(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GameMenu)
{
    ui->setupUi(this);
}

GameMenu::~GameMenu()
{
    delete ui;
}
