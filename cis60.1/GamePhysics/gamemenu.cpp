#include "gamemenu.h"
#include "ui_gamemenu.h"


GameMenu::GameMenu(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GameMenu)
{
    ui->setupUi(this);
    ui->simulationComboBox->addItem("Simple Collision");
    ui->simulationComboBox->addItem("Advanced Collision");

    connect(ui->runSimulation,SIGNAL(clicked()),this,SLOT(runSimulation()));
    mainView = NULL;
    scene = new QGraphicsScene(this);
    this->setFocus();
}

void GameMenu::runSimulation(){
    scene->clear();
    qDebug() << "val: " << ui->simulationComboBox->currentIndex() << " str: " << ui->simulationComboBox->currentText();
    if (mainView != NULL){
        delete mainView;
    }
    mainView = new SimpleCollisionView(scene,this->ui->mainFrame);
    this->mainView->show();
    this->mainView->setFocus();
}


GameMenu::~GameMenu()
{
    delete mainView;
    delete scene;
    delete ui;
}
