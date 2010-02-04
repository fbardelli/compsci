#ifndef PEOPLE_H
#define PEOPLE_H
#include "people.h"
#endif
#ifndef SUSPECT_H
#define SUSPECT_H
#include "suspect.h"
#endif



class cab : public people {
public:
  cab() { 
    set((rand() % WORLD_SIZE), (rand() % WORLD_SIZE));
    setSpeed(3);
  }
  void print() const { 
    cout << "cab is at: " << "(" << getX() << "," << getY() << ")" << endl; 
  }
  void defeated() { cout << "defeated." << endl; }
  void engage(suspect s);
};


