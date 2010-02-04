#include "world.h"

void world::print() const {
  p.print();
  cb.print();
  for (int i = 0; i != NUM_SUSPECTS; i++ )
    s[i].print();
  for (int i = 0; i != NUM_CIVILIANS; i++ )
    c[i].print();
}

void world::set ( int i, int x, int y ) {
  s[i].set(x,y);
}


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
      c[i].move();
}

void world::movecab(){
  cb.move();
}


void world::update(){
  for ( int i = 0; i != NUM_SUSPECTS; i++ ){
    if ( s[i].getX() == p.getX() && s[i].getY() == p.getY() && !s[i].isCaught()){
      p.arrest();
      cout << "Patrol has engaged Suspect " << i << endl;
      s[i].defeated();
    }
    if (s[i].getX() == cb.getX() && s[i].getY() == cb.getY() && !s[i].isCaught()){
      if (cb.hasCab()){
        s[i].setSpeed(cb.getSpeed());
        cb.defeated();
        cout << "Suspect " << i << " has a cab.  Speed is now " << s[i].getSpeed() << endl;
      }
    }
    for(int j = 0; j != NUM_CIVILIANS; j++){
      if (s[i].getX() == c[j].getX() && s[i].getY() == c[j].getY() && !s[i].isCaught()){
        if (c[j].getWallet() > 0){
          c[j].setWallet(c[j].getWallet()-20);
          s[i].setWallet(s[i].getWallet()+20);
          c[j].defeated();
          cout << "Suspect " << i << " stole $20 from a civilian.  Suspect has $" << s[i].getWallet() << " Civilian has $" << c[j].getWallet() << endl;
        }
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


