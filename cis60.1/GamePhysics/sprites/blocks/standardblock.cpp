#include "standardblock.h"

StandardBlock::StandardBlock(qreal x, qreal y, qreal width, qreal height) :
    BlockBase(x, y, width, height)
{
    this->setPen(QPen(QColor(Qt::black)));
    this->setHealth(3);
    this->setPoints(100);
    this->setBlockColor();
}

void StandardBlock::registerHit(){
    this->setHealth(this->getHealth()-1);
    this->setBlockColor();
}

void StandardBlock::setBlockColor(){
   QColor blockColor;
   switch (this->getHealth()){
       case 2:
           blockColor = QColor(0,255,0);
           break;
       case 1:
           blockColor = QColor(0,255,255);
           break;
       default:
           blockColor = QColor(0,127,0);
   }

   this->setBrush(QBrush(blockColor,Qt::SolidPattern));
}
