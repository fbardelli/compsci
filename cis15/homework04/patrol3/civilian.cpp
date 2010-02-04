#include "civilian.h"

civilian::civilian() {
  set((rand() % WORLD_SIZE), (rand() % WORLD_SIZE));
  setWallet(100);
}

void civilian::defeated() {
  cout << "civilian was robbed!\n";
}

void civilian::print() const {
  cout << "civilian at: (" << getX() << "," << getY() << ") has $" << getWallet() << " in wallet\n";
}
