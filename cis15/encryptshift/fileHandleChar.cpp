/* $Id$ */
#include "fileHandleChar.h"

fileHandleChar::fileHandleChar() {
  outfile = new ofstream("output.txt");
}

fileHandleChar::~fileHandleChar(){
  //  cout << "time to destroy";
  if (outfile != NULL)
    outfile->close();
}

void fileHandleChar::passToFile(char c) {
  // cout << c << endl;
  outfile->put(c);
}


