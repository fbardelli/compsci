/* $Id$ */
// filename: point.h
#include "common.h"

class point { 
  private:
    int x, y; 
  public:
    point(): x(0), y(0) {}
    int getX() const; 
    int getY() const;
    void set( int x, int y );
    void print() const;
};
