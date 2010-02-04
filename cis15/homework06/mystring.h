#include <iostream>
using  namespace std;
 
class mystring {
  private:
    char * mychars;
    int size;
  public:
    mystring(string st );
    ~mystring();
    void print(int pos) const;
    void print() const;
    void printback(int pos) const;
    void printback() const;
};

