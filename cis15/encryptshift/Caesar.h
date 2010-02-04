/* $Id$ */
#include <stdlib.h>
#include <iostream>

using namespace std;

class Caesar {
  public:
    Caesar();
    Caesar(int s);
    void setShift(int s);
    char encrypt(char c);
    char decrypt(char c);
  private:
    int shift;
};

