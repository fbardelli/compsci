#ifndef PEOPLE_H
#define PEOPLE_H
#include "people.h"
#endif


class patrol : public people {
public:
  patrol() : arrested(0) { set(0,0); setSpeed(2); }
  void print() const { 
    cout << "patrol car is at: " << "(" << getX() << "," << getY() << ")" << endl; 
  }
  //void move();    //overrides the move() of superclass 
  //void move(direction d);
  void defeated() { cout << "defeated." << endl; }
  void arrest();
  bool busy();
private:
  int arrested; 
};


