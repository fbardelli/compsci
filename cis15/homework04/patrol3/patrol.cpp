#include "patrol.h"

patrol::patrol() : arrested(0) { set(0,0); }

void patrol::print() const { 
    cout << "patrol car is at: " << "(" << x << "," << y << ")" << endl; 
}

void patrol::move() {
  direction d;
  d = static_cast<direction>( rand() % 4 );
  move(d);
}

void patrol::move(direction d) {
  int x = getX();
  int y = getY();
  switch(d){
  case north: 
    y = (y + 2) % WORLD_SIZE;
    break;
  case south:
    y = (y - 2) % WORLD_SIZE;
    if (y < 0)
      y += WORLD_SIZE;
    break;
  case east:
    x = (x + 2) % WORLD_SIZE;
    break;
  case west:
    x = (x - 2) % WORLD_SIZE;
    if (x < 0) 
      x += WORLD_SIZE;
  }
  set(x,y);
}

void patrol::arrest(){
  cout << "arrested a suspect!" << endl;
  arrested++;
}

void patrol::defeated() {
  cout << "defeated." << endl;
}

bool patrol::busy(){
  if ( arrested < NUM_SUSPECTS ) 
    return true;
  else
    return false;
}
