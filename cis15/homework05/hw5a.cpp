#include "point.h"
/***************************************************
 * main
 **************************************************/

int main(){
  point *p = new point;
  p->set(4,5);
  cout << "Here is your point: ";
  p->print();
  cout << endl;
  return 0;
}

