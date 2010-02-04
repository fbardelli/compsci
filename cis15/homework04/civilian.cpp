#include "civilian.h"
 
void civilian::defeated() {
  money > 10 ? money -= 10 : money = 0; 
}


