#include "people.h"

void people::move() {
  direction d;
  d = static_cast<direction>( rand() % 4 );
  move(d);
}

void people::move(direction d) {
  int x = getX();
  int y = getY();
  int sp = getSpeed();
  switch(d){
  case north: 
    y = (y + sp) % WORLD_SIZE;
    break;
  case south:
    y = y - sp;
    if (y < 0)
      y = WORLD_SIZE;
    break;
  case east:
    x = (x + sp) % WORLD_SIZE;
    break;
  case west:
    x = (x - sp) % WORLD_SIZE;
    if (x < 0) 
      x = WORLD_SIZE;
  }
  set(x,y);
}


