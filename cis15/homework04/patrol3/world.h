#include "patrol.h"
#include "suspect.h"
#include "cab.h"
#include "civilian.h"
/***************************************************
 * world class 
 **************************************************/

class world{
public:
  void print() const;
  void set ( int i, int x, int y );
  void movepatrol();
  void movesuspects();
  void movecivilians();
  void movecab();
  bool suspectsCaught();
  void update();
private:
  suspect s[NUM_SUSPECTS];
  civilian c[NUM_CIVILIANS];
  patrol p;
  cab  cb;
};
