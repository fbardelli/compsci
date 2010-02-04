#include "point.h"
void point::print() const { cout << "(" <<  x << "," << y << ")"; }
void point::set( int a, int b ) {
    x = a;
    y = b;
}
int point::getX() const { return x; }
int point::getY() const { return y; }

