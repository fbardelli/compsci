/* $Id$ */
#include "fileHandleString.h"

fileHandleString::fileHandleString() {
    infile = new ifstream("output.txt");
    if(infile->fail()){
       cout << "Error: failed to open output.txt for reading\n";
       exit(1);
    }
}

fileHandleString::~fileHandleString(){
  //  cout << "time to destroy";
  if (infile != NULL)
    infile->close();
}

string fileHandleString::getFromFile(){
  string line,output;
  while(getline(*infile, line)){
    output += line + "\n";
  }
  return output;
}
