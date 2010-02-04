#include "world.h"

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
    else if ( s[i].getX() == cb.getX() && s[i].getY() == cb.getY() && !s[i].isCaught()){
      cb.engage(s[i]);
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
