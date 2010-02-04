#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum direction{ north, south, east, west };
const int WORLD_SIZE = 10;
const int NUM_SUSPECTS = 3;
const int NUM_CIVILIANS = 5;

/***************************************************
 * point class 
 **************************************************/
class point{
public:
  point(): x(0), y(0) {}
  void print() const { cout << "(" <<  x << "," << y << ")"; }
  void set( int x, int y ) { 
    this -> x = x; 
    this -> y = y;
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
  virtual void defeated() = 0;
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
      y = WORLD_SIZE;
    break;
  case east:
    x = (x + 1) % WORLD_SIZE;
    break;
  case west:
    x = (x - 1) % WORLD_SIZE;
    if (x < 0) 
      x = WORLD_SIZE;
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
  void move();    //overrides the move() of superclass 
  void move(direction d);
  void defeated() { cout << "defeated." << endl; }
  void arrest();
  bool busy();
private:
  int arrested; 
};

// patrol moves 2 cells towards the same direction
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
    y = (y - 2) % WORLD_SIZE;;
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
  suspect() : caught(false), money(0) { set((rand() % WORLD_SIZE), (rand() % WORLD_SIZE)); }
  void defeated();
  void engage() { money += 10; }
  void print() const { cout << "suspect at: (" << x << "," << y << ") has money: " << money << endl; }
  bool isCaught() { return caught; }
private:
  bool caught;
  int money;
};

// implements the virtual function defeated
void suspect::defeated() {
  cout << "jailed!" << endl;
  caught = true;
  set(0,0);
}

/***************************************************
 * civilian class 
 **************************************************/

class civilian : public people {
public:
  civilian(): money(100){}
  void print() const { cout << "civilian at: (" << x << "," << y << ") has money: " << money <<  endl; }
  void defeated();
  bool hasMoney() { return money; } 
private:
  int money;
};

void civilian::defeated() {
  money > 10 ? money -= 10 : money = 0; 
}

/***************************************************
 * world class 
 **************************************************/

class world{
public:
  void print() const {
    p.print();
    for (int i = 0; i != NUM_SUSPECTS; i++ )
      s[i].print();
    for (int i = 0; i != NUM_CIVILIANS; i++ )
      c[i].print();
  }
  void set ( int i, int x, int y ) {
    s[i].set(x,y);
  }
  void movepatrol();
  void movesuspects();
  void movecivilians();
  bool suspectsCaught();
  void update();
private:
  suspect s[NUM_SUSPECTS];
  civilian c[NUM_CIVILIANS];
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

void world::movecivilians(){
  for ( int i = 0; i != NUM_CIVILIANS; i++ )
    if ( c[i].hasMoney() )
      c[i].move();
}

void world::update(){
  for ( int i = 0; i != NUM_SUSPECTS; i++ ){
    if ( s[i].getX() == p.getX() && s[i].getY() == p.getY() && !s[i].isCaught()){
      p.arrest();
      s[i].defeated();
    }
    else {
      for ( int j = 0; j != NUM_CIVILIANS; j++ )
	if ( s[i].getX() == c[j].getX() && s[i].getY() == c[j].getY() && c[j].hasMoney()){
	  s[i].engage();
	  c[j].defeated();
	}
    }
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
    w.movecivilians();
    w.update();
    w.print();
  }
  return 0;
}

