/***************************************************
 * world class 
 **************************************************/
#include "patrol.h"
#include "civilian.h"
#include "cab.h"
#ifndef SUSPECT_H
#define SUSPECT_H
#include "suspect.h"
#endif


class world{
public:
  void print() const {
    p.print();
    for (int i = 0; i != NUM_SUSPECTS; i++ )
      s[i].print();
    for (int i = 0; i != NUM_CIVILIANS; i++ )
      c[i].print();
  }
  void set ( int i, int x, int y ) {
    s[i].set(x,y);
  }
  void movepatrol();
  void movesuspects();
  void movecivilians();
  bool suspectsCaught();
  void update();
private:
  suspect s[NUM_SUSPECTS];
  civilian c[NUM_CIVILIANS];
  patrol p;
  cab cb;
};


