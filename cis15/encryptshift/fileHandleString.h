/* $Id$ */
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

class fileHandleString{
  public:
    fileHandleString();
    ~fileHandleString();
    string getFromFile();
  private:
    ifstream * infile;
};

