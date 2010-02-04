/***************************************************
 * main
 **************************************************/
#include "world.h"
#include <stdlib.h>

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
