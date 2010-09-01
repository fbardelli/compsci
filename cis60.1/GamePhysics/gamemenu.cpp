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
    Direction dir;
    switch(e->key()){
        case Qt::Key_Up:
            dir = Up;
            r.setY(r.y()-15);
            if(r.y() < 0){
                r.setY(0);
            }
            break;
        case Qt::Key_Down:
            dir = Down;
            r.setY(r.y()+15);
            if( (r.y() + 50) > boardHeight){
                r.setY(boardHeight-50);
            }
            break;
        case Qt::Key_Left:
            dir = Left;
            r.setX(r.x()-15);
            if(r.x()-15 < 0){
                r.setX(0);
            }
            break;
        case Qt::Key_Right:
            dir = Right;
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
    if(objectsCollide(r,obstacle->rect())){
        qDebug() << "Objects collide";
        moveToEdge(r,obstacle->rect(),dir);
    }
    r.setWidth(50);
    r.setHeight(50);
    player->setRect(r);

}

void GameMenu::moveToEdge(QRectF &p, QRectF o, Direction dir){
    if(dir == Right){
        qDebug() << "px:" << p.x() << " ox:" << o.x() << " pw:" << p.width() << " ow:" << o.width();
        p.setX( (o.x()-o.width()));
    }else if (dir == Left){
        p.setX(o.x()+o.width()+1);
    }else if (dir == Down){
        p.setY( (o.y()-o.height()) );
    }else if (dir == Up){
        p.setY(o.y()+o.height()+1);
    }

}

bool GameMenu::objectsCollide(QRectF p, QRectF o){
    int pLeft = p.x();
    int oLeft = o.x();
    int pRight = p.x() + p.width();
    int oRight = o.x() + o.width();
    int pTop   = p.y();
    int oTop   = o.y();
    int pBottom = p.y() + p.height();
    int oBottom = o.y() + o.height();
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
