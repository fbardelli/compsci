/* $Id */
// filename: testpoint.cpp
#include <iostream>
using namespace std;
#include "cab.h"
#include "time.h"

int main() { 
  cab cb; 
  srand(time(NULL));
  cb.set( 1, 2 ); 
  cb.print();
  cout << "moving randomly in one direction\n";
  cb.move();
  cb.print();
  cout << "cab " << (cb.hasCab() ? "has" : "lost") << " his car" << endl;
  cout << "Cab speed is " << cb.getSpeed() << endl;
  cb.defeated();
  cout << "cab " << (cb.hasCab() ? "has" : "lost") << " his car" << endl;
  cout << "Cab speed is " << cb.getSpeed() << endl;
  cb.print();
}
