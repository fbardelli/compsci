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
    rect = scene->addRect(QRectF(200, 200, 50, 50),QPen(QColor(Qt::black)),QBrush(Qt::red,Qt::SolidPattern));
    //QGraphicsItem *item = scene.itemAt(50, 50);
    this->ui->graphicsView->setScene(scene);
    this->ui->graphicsView->show();
    this->setFocus();
}

void GameMenu::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Up:
            qDebug() << "up pressed";
            if(rect->y() > 0){
                rect->setY(rect->y()-15);

            }
            break;
        case Qt::Key_Down:
            qDebug() << "down pressed";
            if( (rect->y() + 65) < ui->graphicsView->height()){
                rect->setY(rect->y()+15);
            }
            break;
        case Qt::Key_Left:
            qDebug() << "left pressed";
            if(rect->x() > 0){
                rect->setX(rect->x()-15);
            }
            break;
        case Qt::Key_Right:
            qDebug() << "right pressed";
            if( (rect->x() + 65) < ui->graphicsView->width()){
                rect->setX(rect->x()+15);
            }
            break;
    }


}

GameMenu::~GameMenu()
{
    delete ui;
    delete scene;
}
