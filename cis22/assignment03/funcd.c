#include "stdio.h"

/*int flux(int,int,int);*/

int flux(a,b,c)
int a,b,c;
{
  return a+b+c;
}

int main(){
  int b = flux(1,2,3);
  printf("%d\n",b);
  return 0;
}
