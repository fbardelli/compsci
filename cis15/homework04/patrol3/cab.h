#ifndef PEOPLE_H
#define PEOPLE_H
#include "people.h"
#endif


class cab : public people {
public:
  cab();
  void print() const;
  void defeated();
  bool hasCab();
private:
  bool cabStolen;
};

