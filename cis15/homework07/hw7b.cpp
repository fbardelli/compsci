#include <cstring>
#include <iostream>
#include <list>


using namespace std;
int main() {
  char *tmp = const_cast<char *>("hello");
  list<char> A(0);
  for( int i=0; i < strlen(tmp); i++ ){
    A.push_back( tmp[i]);
  }
  while( A.size() > 0 ){
    cout << A.front() << " ";
    A.pop_front();
  }
  cout << endl;
}
