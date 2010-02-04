#include "globals.h"
/***************************************************
 * point class 
 **************************************************/
class point{
public:
  point(): x(0), y(0) {}
  void print() const;
  void set( int a, int b );
  int getX() const;
  int getY() const;
protected:
  int x, y;
};

