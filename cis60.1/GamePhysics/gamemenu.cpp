#include "gamemenu.h"
#include "ui_gamemenu.h"


GameMenu::GameMenu(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GameMenu)
{
    ui->setupUi(this);
    ui->simulationComboBox->addItem("Simple Collision");
    ui->simulationComboBox->addItem("Advanced Collision");
    ui->simulationComboBox->addItem("Acceleration");
    ui->simulationComboBox->addItem("Gravity");
    ui->simulationComboBox->addItem("Projectile");
    ui->simulationComboBox->addItem("Inelastic Collision");
    ui->simulationComboBox->addItem("Thrust and Lift");
    ui->simulationComboBox->addItem("Deflection");
    ui->simulationComboBox->addItem("Object Interaction");
    ui->simulationComboBox->addItem("Block Breaker");



    //this->setStyleSheet("QMainWindow { background-color: yellow }");
    connect(ui->runSimulation,SIGNAL(clicked()),this,SLOT(runSimulation()));
    mainView = NULL;
    scene = new QGraphicsScene(this);
    this->setFocus();
}

void GameMenu::runSimulation(){
    scene->clear();
    //qDebug() << "val: " << ui->simulationComboBox->currentIndex() << " str: " << ui->simulationComboBox->currentText();
    if (mainView != NULL){
        delete mainView;
    }
    switch(ui->simulationComboBox->currentIndex()){
        case 0:
            mainView = new SimpleCollisionView(scene,this->ui->mainFrame);
            break;
        case 1:
            mainView = new AdvancedCollisionView(scene,this->ui->mainFrame);
            break;
        case 2:
            mainView = new AccelerateView(scene,this->ui->mainFrame);
            break;
        case 3:
            mainView = new GravityView(scene,this->ui->mainFrame);
            break;
        case 4:
            mainView = new ProjectileView(scene,this->ui->mainFrame);
            break;
        case 5:
            mainView = new InelasticCollisionView(scene,this->ui->mainFrame);
            break;
        case 6:
            mainView = new ThrusterView(scene,this->ui->mainFrame);
            break;
        case 7:
            mainView = new DeflectionView(scene,this->ui->mainFrame);
            break;
        case 8:
            mainView = new ObjectInteractionView(scene,this->ui->mainFrame);
            break;
        case 9:
            mainView = new BlockBreakerView(scene,this->ui->mainFrame);
            break;
    default:
            mainView = new SimpleCollisionView(scene,this->ui->mainFrame);
            break;
    }
    ui->textDisplay->setHtml(mainView->getInstructions());
    mainView->show();
    mainView->setFocus();
}


GameMenu::~GameMenu()
{
    delete mainView;
    delete scene;
    delete ui;
}
