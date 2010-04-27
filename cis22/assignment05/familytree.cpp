/*  Frank Bardelli
 *  CIS 22 Data Structures
 *  Assignment #5
 *  April 24, 2010
 */
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstring>
using namespace std;

#include "family.h"

FamilyMember * parseInputFile(ifstream& in);

int main(){
  ifstream inputFile;
  inputFile.open("tree.dat");
  FamilyMember * tree = parseInputFile(inputFile);
  return 0;
}

FamilyMember * parseInputFile(ifstream& in){
  FamilyMember * f = new FamilyMember("Jones",3);
  return f;
}

