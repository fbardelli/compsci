/* $Id */
// filename: testpoint.cpp
#include <iostream>
using namespace std;
#include "civilian.h"
#include "time.h"

int main() { 
  civilian c; 
  srand(time(NULL));
  c.set( 1, 2 ); 
  c.print();
  cout << "moving randomly in one direction\n";
  c.move();
  c.print();
  cout << "Civilian has $" << c.getWallet() << endl;
  c.defeated();
  c.setWallet(c.getWallet()-20);
  cout << "Civilian has $" << c.getWallet() << endl;
  c.print();
}
