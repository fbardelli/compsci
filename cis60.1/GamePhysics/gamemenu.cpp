#include "gamemenu.h"
#include "ui_gamemenu.h"

GameMenu::GameMenu(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GameMenu)
{
    ui->setupUi(this);
    ui->simulationComboBox->addItem("Simple Collision");
    connect(ui->runSimulation,SIGNAL(clicked()),this,SLOT(runSimulation()));
    scene = new QGraphicsScene(this);
    this->setFocus();
}

void GameMenu::runSimulation(){
    qDebug("run Pressed");
    rect = scene->addRect(QRectF(200, 200, 100, 100),QPen(QColor(Qt::black)),QBrush(Qt::red,Qt::SolidPattern));
    scene->addText("Hello, world!", QFont("Times", 10, QFont::Bold));
    //QGraphicsItem *item = scene.itemAt(50, 50);
    this->ui->graphicsView->setScene(scene);
    this->ui->graphicsView->show();
    //connect(this,SIGNAL(key_pressed(QKeyEvent&)),this,SLOT(handleKeyPress(QKeyEvent&)));
}

void GameMenu::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Up:
            qDebug() << "up pressed";
            rect->setY(rect->y()-10);
            break;
        case Qt::Key_Down:
            qDebug() << "down pressed";
            rect->setY(rect->y()+10);
            break;
        case Qt::Key_Left:
            qDebug() << "left pressed";
            rect->setX(rect->x()-10);
            break;
        case Qt::Key_Right:
            qDebug() << "right pressed";
            rect->setX(rect->x()+10);
            break;
    }


}

GameMenu::~GameMenu()
{
    delete ui;
    delete scene;
}
