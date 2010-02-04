#include "suspect.h"

// implements the virtual function defeated
void suspect::defeated() {
  cout << "jailed!" << endl;
  caught = true;
  set(0,0);
}
