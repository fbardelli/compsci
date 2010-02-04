#include "cab.h"


void cab::engage(suspect s){
  cout << "cab stolen!" << endl;
  s.setSpeed(3);
  setSpeed(1);
}
