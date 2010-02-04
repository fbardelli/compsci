#ifndef PEOPLE_H
#define PEOPLE_H
#include "people.h"
#endif

/***************************************************
 * civilian class 
 **************************************************/

class civilian : public people {
public:
  civilian(): money(100){}
  void print() const { cout << "civilian at: (" << getX() << "," << getY() << ") has money: " << money <<  endl; }
  void defeated();
  bool hasMoney() { return money; } 
private:
  int money;
};


