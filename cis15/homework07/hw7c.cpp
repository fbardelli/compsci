#include <cstring>
#include <iostream>
#include <list>


using namespace std;
int main() {
  char *tmp = const_cast<char *>("hello");
  list<char> A(0);
  list<char>::iterator the_iterator;
  for( int i=0; i < strlen(tmp); i++ ){
    A.push_back( tmp[i]);
  }
  the_iterator = A.begin();
  while( the_iterator != A.end() ) {
    cout << *the_iterator++ << " ";
  }
  cout << endl;
}
