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
#include<queue>
using namespace std;

#include "family.h"

FamilyMember * parseInputFile(ifstream& in);

struct Father {
  FamilyMember * p;
  int numSons; 
};

int main(){
  ifstream inputFile;
  inputFile.open("tree.dat");
  FamilyMember * familytree = parseInputFile(inputFile);
  cout << familytree->getSons().size() << "\n";
  return 0;
}

FamilyMember * parseInputFile(ifstream& in){
  string line;
  queue<Father> fathers;
  FamilyMember * ancestor = NULL;
  while (getline(in,line) && ! in.eof()){
     string name = line.substr(0,line.find('\t'));
     int num = atoi( (line.substr(line.find('\t')+1)).c_str() );
     FamilyMember * member = new FamilyMember(name,num);
     if(ancestor == NULL && fathers.size() == 0) {
       ancestor = member;
       Father father  = {ancestor, num};
       fathers.push(father);
     }else if(fathers.size() >= 1){
       if(num >= 1){
         Father father  = {member, num};
         fathers.push(father);
       }
       Father f = fathers.front();
       if (f.numSons < 1) {
         if(fathers.size() > 1){
           fathers.pop();
           f = fathers.front();
         }else{
           cout << "Error: there are no valid fathers left\n";
         }
       }
       cout << "adding " << member->getName() << " son of  " <<f.p->getName() << endl;
       f.p->addSon(member);
       cout << f.p->getName() << " had " << f.numSons << " sons\n";
       f.numSons = f.numSons -1;
       cout << f.p->getName() << " has " << f.numSons << " sons\n";
       cout << "fs" << fathers.size() << endl;
     }else{
           cout << "Error: there are no valid fathers left\n";
     }
  }
  return ancestor;
}

