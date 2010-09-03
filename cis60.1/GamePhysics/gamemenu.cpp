#include "gamemenu.h"
#include "ui_gamemenu.h"

#define SQUARE_SIZE 50
#define MOVE_DISTANCE 15

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
    player = scene->addRect(QRectF(0, 0, SQUARE_SIZE, SQUARE_SIZE),QPen(QColor(Qt::black)),QBrush(Qt::red,Qt::SolidPattern));
    obstacle = scene->addRect(QRectF(200, 200, SQUARE_SIZE, SQUARE_SIZE),QPen(QColor(Qt::black)),QBrush(Qt::blue,Qt::SolidPattern));
    this->ui->graphicsView->show();
    this->setFocus();
}

void GameMenu::keyPressEvent(QKeyEvent *e){
    QRectF r = player->rect();
    int boardWidth  = ui->graphicsView->width();
    int boardHeight = ui->graphicsView->height();
    Direction dir;
    switch(e->key()){
        case Qt::Key_Up:
            dir = Up;
            r.moveTo(r.x(),r.y()-MOVE_DISTANCE);
            if(r.y() < 0){
                r.moveTo(r.x(),0);
            }
            break;
        case Qt::Key_Down:
            dir = Down;
            r.moveTo(r.x(),r.y()+MOVE_DISTANCE);
            if( (r.y() + SQUARE_SIZE) > boardHeight){
                r.moveTo(r.x(),boardHeight-SQUARE_SIZE);
            }
            break;
        case Qt::Key_Left:
            dir = Left;
            r.moveTo(r.x()-MOVE_DISTANCE,r.y());
            if(r.x()-MOVE_DISTANCE < 0){
                r.moveTo(0,r.y());
            }
            break;
        case Qt::Key_Right:
            dir = Right;
            r.moveTo(r.x()+MOVE_DISTANCE,r.y());
            if( (r.x() + SQUARE_SIZE) > boardWidth){
                r.moveTo(boardWidth - SQUARE_SIZE,r.y());
            }
            break;
    }
    qDebug() << " X: " << r.x()
             << " Y: " << r.y()
             << " w: " << this->ui->graphicsView->width()
             << " h: " << this->ui->graphicsView->height();
    if(objectsCollide(r,obstacle->rect())){
        qDebug() << "Objects collide";
        moveToEdge(r,obstacle->rect(),dir);
    }
    //r.setWidth(SQUARE_SIZE);
    //r.setHeight(SQUARE_SIZE);
    player->setRect(r);

}

void GameMenu::moveToEdge(QRectF &p, QRectF o, Direction dir){
    if(dir == Right){
        qDebug() << "px:" << p.x() << " ox:" << o.x() << " pw:" << p.width() << " ow:" << o.width();
        p.moveTo( (o.x()-SQUARE_SIZE-1),p.y());
    }else if (dir == Left){
        p.moveTo(o.x()+SQUARE_SIZE+1,p.y());
    }else if (dir == Down){
        p.moveTo(p.x(), (o.y()-SQUARE_SIZE-1) );
    }else if (dir == Up){
        p.moveTo(p.x(),o.y()+SQUARE_SIZE+1);
    }

}

bool GameMenu::objectsCollide(QRectF p, QRectF o){
    int pLeft = p.x();
    int oLeft = o.x();
    int pRight = p.x() + SQUARE_SIZE;
    int oRight = o.x() + SQUARE_SIZE;
    int pTop   = p.y();
    int oTop   = o.y();
    int pBottom = p.y() + SQUARE_SIZE;
    int oBottom = o.y() + SQUARE_SIZE;
    // is player fully above obstacle?
    if (pBottom < oTop) return false;
    // is player fully below obstacle?
    if (pTop > oBottom) return false;
    //Is player to the right of obstacle?
    if (pRight < oLeft) return false;
    //Is player to the left of obstacle?
    if (pLeft > oRight) return false;
    //otherwise player collides with obstacle.
    return true;
}

GameMenu::~GameMenu()
{
    delete ui;
    delete scene;
}
