/* $Id$ */
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

class fileHandleChar{
  public:
    fileHandleChar();
    ~fileHandleChar();
    void passToFile(char c);
  private:
    ofstream * outfile;
};

