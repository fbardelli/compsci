#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum direction{ north, south, east, west };
const int WORLD_SIZE = 10;
const int NUM_SUSPECTS = 3;

/***************************************************
 * point class 
 **************************************************/
class point{
public:
  point(): x(0), y(0) {}
  void print() const { cout << "(" <<  x << "," << y << ")"; }
  void set( int a, int b ) {
    x = a;
    y = b;
  }
  int getX() const { return x; }
  int getY() const { return y; }
protected:
  int x, y;
};

/***************************************************
 * people class 
 **************************************************/
class people : public point {
public:
  void move();
  void move( direction d );
};

void people::move() {
  direction d;
  d = static_cast<direction>( rand() % 4 );
  move(d);
}

void people::move(direction d) {
  int x = getX();
  int y = getY();
  switch(d){
  case north: 
    y = (y + 1) % WORLD_SIZE;
    break;
  case south:
    y = y - 1;
    if (y < 0)
      y += WORLD_SIZE;
    break;
  case east:
    x = (x + 1) % WORLD_SIZE;
    break;
  case west:
    x = x - 1;
    if (x < 0) 
      x += WORLD_SIZE;
  }
  set(x,y);
}

/***************************************************
 * patrol class 
 **************************************************/

class patrol : public people {
public:
  patrol() : arrested(0) { set(0,0); }
  void print() const { 
    cout << "patrol car is at: " << "(" << x << "," << y << ")" << endl; 
  }
  void move();
  void move(direction d);
  void arrest();
  bool busy();
private:
  int arrested; 
};

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

bool patrol::busy(){
  if ( arrested < NUM_SUSPECTS ) 
    return true;
  else
    return false;
}


/***************************************************
 * suspect class 
 **************************************************/

class suspect : public people{
public: 
  suspect() : caught(false) { set((rand() % WORLD_SIZE), (rand() % WORLD_SIZE)); }
  void jailed() {
    cout << "jailed!" << endl;
    caught = true;
    set(0,0);
  }
  void print() const { cout << "suspect at: (" << x << "," << y << ")" << endl; }
  bool isCaught() { return caught; }
private:
  bool caught;
};

/***************************************************
 * world class 
 **************************************************/

class world{
public:
  void print() const {
    p.print();
    for (int i = 0; i != NUM_SUSPECTS; i++ )
      s[i].print();
  }
  void set ( int i, int x, int y ) {
    s[i].set(x,y);
  }
  void movepatrol();
  void movesuspects();
  bool suspectsCaught();
  void update();
private:
  suspect s[NUM_SUSPECTS];
  patrol p;
};

void world::movepatrol(){
  p.move();
}

void world::movesuspects(){
  for ( int i = 0; i != NUM_SUSPECTS; i++ )
    if ( !s[i].isCaught() )
      s[i].move();
}

void world::update(){
  for ( int i = 0; i != NUM_SUSPECTS; i++ )
    if ( s[i].getX() == p.getX() && s[i].getY() == p.getY() && !s[i].isCaught()){
      p.arrest();
      s[i].jailed();
    }
}

bool world::suspectsCaught() {
  bool suspects_arrested = true;
  for ( int i = 0; i != NUM_SUSPECTS; i++ ) 
    if ( !s[i].isCaught() ) 
      suspects_arrested = false;
  return suspects_arrested;
}

/***************************************************
 * main
 **************************************************/

int main(){
  srand(time(NULL));
  world w;
  while( ! w.suspectsCaught() ) {
    w.movepatrol(); 
    w.movesuspects();
    w.update();
    w.print();
  }
  return 0;
}

