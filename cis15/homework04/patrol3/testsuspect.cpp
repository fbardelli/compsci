/* $Id */
// filename: testpoint.cpp
#include <iostream>
using namespace std;
#include "suspect.h"
#include "time.h"

int main() { 
  suspect s; 
  srand(time(NULL));
  s.set( 1, 2 ); 
  s.print();
  cout << "moving randomly in one direction\n";
  s.move();
  s.print();
  cout << "suspect " << (s.isCaught() ? "caught" : "free") << endl;
  cout << "Arresting\n";
  s.defeated();
  s.print();
  cout << "suspect " << (s.isCaught() ? "caught" : "free") << endl;
}
