#include "world.h"
/***************************************************
 * main
 **************************************************/

int main(){
  srand(time(NULL));
  world w;
  w.print(); 
  cout << "moving patrol\n";
  w.movepatrol(); 
  w.print(); 
  cout << "moving suspects\n";
  w.movesuspects(); 
  w.print();
  int moves = 0;
  cout << "running simulation until all suspects are caught\n"; 
  while( ! w.suspectsCaught() ) {
    w.movepatrol(); 
    w.movesuspects();
    w.movecivilians();
    w.movecab();
    w.update();
    moves++;
  }
  cout << "all suspects caught in "<<moves << " moves\n";
  return 0;
}

