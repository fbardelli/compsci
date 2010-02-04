#include "patrol.h"

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


