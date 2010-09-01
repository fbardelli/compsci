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
    //QGraphicsItem *item = scene.itemAt(50, 50);
    this->ui->graphicsView->setScene(scene);
    this->ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(0,0,this->ui->graphicsView->width(),this->ui->graphicsView->height());
    player = scene->addRect(QRectF(0, 0, 50, 50),QPen(QColor(Qt::black)),QBrush(Qt::red,Qt::SolidPattern));
    obstacle = scene->addRect(QRectF(200, 200, 50, 50),QPen(QColor(Qt::black)),QBrush(Qt::blue,Qt::SolidPattern));
    this->ui->graphicsView->show();
    this->setFocus();
}

void GameMenu::keyPressEvent(QKeyEvent *e){
    QRectF r = player->rect();
    int boardWidth  = ui->graphicsView->width();
    int boardHeight = ui->graphicsView->height();
    switch(e->key()){
        case Qt::Key_Up:
            qDebug() << "up pressed";
            r.setY(r.y()-15);
            if(r.y() < 0){
                r.setY(0);
            }
            break;
        case Qt::Key_Down:
            qDebug() << "down pressed";
            r.setY(r.y()+15);
            if( (r.y() + 50) > boardHeight){
                r.setY(boardHeight-50);
            }
            break;
        case Qt::Key_Left:
            qDebug() << "left pressed";
            r.setX(r.x()-15);
            if(r.x()-15 < 0){
                r.setX(0);
            }
            break;
        case Qt::Key_Right:
            qDebug() << "right pressed";
            r.setX(r.x()+15);
            if( (r.x() + 50) > boardWidth){
                r.setX(boardWidth - 50);
            }
            break;
    }
    qDebug() << " X: " << r.x()
             << " Y: " << r.y()
             << " w: " << this->ui->graphicsView->width()
             << " h: " << this->ui->graphicsView->height();
    r.setWidth(50);
    r.setHeight(50);
    player->setRect(r);

}

GameMenu::~GameMenu()
{
    delete ui;
    delete scene;
}
