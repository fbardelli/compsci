#ifndef PEOPLE_H
#define PEOPLE_H
#include "people.h"
#endif


/***************************************************
 * suspect class 
 **************************************************/

class suspect : public people{
public: 
  suspect();
  void defeated();  
  void print() const;
  bool isCaught();
private:
  bool caught;
};


