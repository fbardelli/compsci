#include "world.h"
/***************************************************
 * main
 **************************************************/

int main(){
  srand(time(NULL));
  world w;
  while( ! w.suspectsCaught() ) {
    w.movepatrol(); 
    w.movecab(); 
    w.movesuspects();
    w.update();
    w.print();
  }
  return 0;
}

