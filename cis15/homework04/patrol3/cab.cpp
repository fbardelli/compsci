#include "cab.h"

cab::cab() { 
  set((rand() % WORLD_SIZE), (rand() % WORLD_SIZE));
  cabStolen = false;
  setSpeed(3);
}

bool cab::hasCab(){
  return ! cabStolen;
}

void cab::defeated() { 
  cout << "cab stolen" << endl;
  setSpeed(1);
  cabStolen = true;
}

void cab::print() const { 
    cout << "cab is at: " << "(" << getX() << "," << getY() << ")" << endl; 
}

