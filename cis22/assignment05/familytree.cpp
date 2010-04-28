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


int main(){
  ifstream inputFile;
  inputFile.open("tree.dat");
  FamilyMember * familytree = parseInputFile(inputFile);
  cout << familytree->getSons().size() << "\n";
  return 0;
}

FamilyMember * parseInputFile(ifstream& in){
  string line;
  queue<FamilyMember *> fathers;
  FamilyMember * ancestor = NULL;
  while (getline(in,line) && ! in.eof()){
     /* parse record, get name and number of sons */
     string name = line.substr(0,line.find('\t'));
     int numSons = atoi( (line.substr(line.find('\t')+1)).c_str() );
     FamilyMember * member = new FamilyMember(name);

     /* The first record is the ancestor of the others */
     if(ancestor == NULL){
       ancestor = member;
     }else{
       /* All other records have a father we've seen */
       if(! fathers.empty()){
         /* take a father off the top of the stack */
         FamilyMember * father = fathers.front();
         fathers.pop();
         father->addSon(member);
       } else {
         cout << "Error: no more fathers\n";
       }
     }
     /* maintain a queue of pointers to fathers,
        if a father has multiple sons store it once for
        each son 
     */
     for(int i = 0; i < numSons; i++){
       fathers.push(member);
     }
  }
  return ancestor;
}

