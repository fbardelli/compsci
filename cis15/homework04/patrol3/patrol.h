#ifndef PEOPLE_H
#define PEOPLE_H
#include "people.h"
#endif
/***************************************************
 * patrol class 
 **************************************************/

class patrol : public people {
public:
  patrol();
  void print() const;
  void move();
  void move(direction d);
  void defeated();
  void arrest();
  bool busy();
private:
  int arrested; 
};


