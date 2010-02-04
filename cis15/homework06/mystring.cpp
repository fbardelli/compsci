#include "mystring.h"

mystring::mystring(string st){
  size = st.length();
  mychars = new char[size];
  for (int i = 0; i < size ;i++){
    mychars[i] = st[i];
  }
}

mystring::~mystring(){
  delete[] mychars;
}

/* 
  Overloading print so if called with no args starts at position 0
  This way the caller doesn't need to be aware of the implementation. 
*/
void mystring::print() const{
  print(0);
}

void mystring::print(int pos) const{
  if (pos < size){
    cout << mychars[pos];
    print(pos+1);
  }
}

/* 
  Overloading printback so if called with no args starts at the end of mystring. 
  This way the caller doesn't need to be aware of the implementation. 
*/

void mystring::printback() const{
  printback(size-1);
}

void mystring::printback(int pos) const{
  cout << mychars[pos];
  if (pos >= 1){
    printback(pos-1);
  }
}

