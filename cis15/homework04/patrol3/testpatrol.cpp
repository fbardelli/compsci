/* $Id */
// filename: testpoint.cpp
#include <iostream>
using namespace std;
#include "patrol.h"
#include "time.h"

int main() { 
  patrol p; 
  srand(time(NULL));
  p.set( 1, 2 ); 
  p.print();
  cout << "moving randomly in one direction\n";
  p.move();
  p.print();
  int arrest_attempts = 0;
  while (p.busy()){
    p.arrest();
    arrest_attempts++;
    cout << "arrested " << arrest_attempts << " suspects\n";
  }
  cout << "All suspects arrested\n";
}
