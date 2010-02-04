#include "point.h"

class people : public point {
public:
  people() : speed(1), wallet(0){ };
  void setSpeed(int sp);
  int getSpeed() const; 
  void setWallet(int w);
  int getWallet() const; 
  void move();
  void move( direction d );  
  virtual void defeated() = 0;
private:
  int speed;
  int wallet;
};
