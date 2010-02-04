#include "point.h"

class people : public point {
public:
  people(){ setSpeed(1); };
  void setSpeed(int sp){ speed = sp;}; 
  int getSpeed(){ return speed; }; 
  void move();
  void move( direction d );  
  virtual void defeated() = 0;
private:
  int speed;
};
