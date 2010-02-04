#include "suspect.h"

suspect::suspect() : caught(false) {
  set((rand() % WORLD_SIZE), (rand() % WORLD_SIZE));
}

void suspect::defeated() {
  cout << "jailed!" << endl;
  caught = true;
  set(0,0);
}

void suspect::print() const { 
  cout << "suspect at: (" << x << "," << y << ")" << endl; 
}

bool suspect::isCaught() { 
  return caught;
}

