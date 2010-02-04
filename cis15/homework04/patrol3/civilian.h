#ifndef PEOPLE_H
#define PEOPLE_H
#include "people.h"
#endif

/***************************************************
 * civilian class 
 **************************************************/

class civilian : public people {
public:
  civilian();
  void print() const;
  void defeated();
  bool hasMoney() { return getWallet() > 0; } 
};
