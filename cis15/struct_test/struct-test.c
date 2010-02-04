#include "stdio.h";

int main(){
  struct St {
    int  i;
    char c;
  };
  struct St s1;
  s1.i = 1;
  s1.c = 'A';
  
  //works with gcc and g++
  struct St s2 = { i : 2, c : 'B'};
  printf("s1: %d %c\n",s1.i,s1.c);
  printf("s2: %d %c\n",s2.i,s2.c);
#ifdef __cplusplus
  class Cl {
   public:
    int  i;
    char c;
  };
  
  Cl c1 = { i:3, c:'C'};
  printf("c2: %d %c\n",c1.i,c1.c);
#else
  //This only works with gcc
  struct St s3 = { .i = 4, .c ='D'};
  printf("s3: %d %c\n",s3.i,s3.c);
#endif
  return 0;
}
