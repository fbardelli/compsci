#include "mystring.h"

int main(int argc, char * argv[] ){
  string message;
  cout << "Enter a string: ";
  getline(cin, message);
  mystring m(message);
  m.print();
  cout << endl;
  m.printback();
  cout << endl;
  return 0;
}
