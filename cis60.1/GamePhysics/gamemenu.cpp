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
    QRectF r = rect->rect();
    switch(e->key()){
        case Qt::Key_Up:
            qDebug() << "up pressed";
            if(r.y() > 0){
                r.setY(r.y()-15);
            }
            break;
        case Qt::Key_Down:
            qDebug() << "down pressed";
            if( (r.y() + 65) < ui->graphicsView->height()){
                r.setY(r.y()+15);
            }
            break;
        case Qt::Key_Left:
            qDebug() << "left pressed";
            if(r.x() > 0){
                r.setX(r.x()-15);
            }
            break;
        case Qt::Key_Right:
            qDebug() << "right pressed";
            if( (r.x() + 65) < ui->graphicsView->width()){
                r.setX(r.x()+15);
            }
            break;
    }
    r.setWidth(50);
    r.setHeight(50);
    rect->setRect(r);

}

GameMenu::~GameMenu()
{
    delete ui;
    delete scene;
}
