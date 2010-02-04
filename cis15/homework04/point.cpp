/* $Id$ */
// filename: point.cpp
#include "point.h"

int point::getX() const { 
  return x;
}

int point::getY() const { 
  return y;
}

void point::set( int x, int y ) {
  this->x = x;
  this->y = y;
}

void point::print() const { 
  cout << "(" << x << ", " << y << ")" << endl;
}
