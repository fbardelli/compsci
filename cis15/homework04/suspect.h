#ifndef PEOPLE_H
#define PEOPLE_H
#include "people.h"
#endif

class suspect : public people{
public: 
  suspect() : caught(false), money(0) { set((rand() % WORLD_SIZE), (rand() % WORLD_SIZE)); }
  void defeated();
  void engage() { money += 10; }
  void print() const { cout << "suspect at: (" << getX() << "," << getY() << ") has money: " << money << endl; }
  bool isCaught() { return caught; }
private:
  bool caught;
  int money;
};


