#include <cstring>
#include <iostream>
#include "elements.h"


using namespace std;
int main() {
  char *tmp = const_cast<char *>("hello");
  Elements<char> A(5);
  for( int i=0; i < strlen(tmp); i++ ){
    A.set( i, tmp[i]);
  }
  for( int i=0; i < A.getSize(); i++ ){
    cout << A.get( i ) << " ";
  }
  cout << endl;
}
