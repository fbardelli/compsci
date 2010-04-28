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
#include<list>
using namespace std;
#include <sstream> // header file for string stream processing
using std::ostringstream; // stream insertion operators


#include "family.h"

FamilyMember * parseInputFile(ifstream& in);
void printFamilyReport(FamilyMember * f);
string readFamilyList(list<FamilyMember *> fl);
string displayIfExists(FamilyMember * f);
void freeFamilyTree(FamilyMember * f);

void printFamilyReport(FamilyMember * f){
  cout << f->getName() << ":"
       << "\n\t Father: " << displayIfExists(f->getParent())
       << "\n\t Grandfather: " << displayIfExists(f->getGrandparent())
       << "\n\t Youngest Brother(excluding self): " << displayIfExists(f->getYoungestBrother())
       << "\n\t Oldest Brother(excluding self): " << displayIfExists(f->getOldestBrother())
       << "\n\t Youngest Son: " << displayIfExists(f->getYoungestSon())
       << "\n\t Oldest Son: " << displayIfExists(f->getOldestSon())
       << "\n\t Brothers:" << readFamilyList(f->getBrothers())
       << "\n\t Sons:" << readFamilyList(f->getSons())
       << "\n\t Uncles:" << readFamilyList(f->getUncles())
       << endl;
}

void freeFamilyTree(FamilyMember * f){
  cout << "freeing " << f->getName() << endl;
  delete f;
}

/* helper method replace name with N/A for NULL nodes*/
string displayIfExists(FamilyMember * f){
  return (f !=NULL ? f->getName() : "N/A");
}

/* convert linked list into a string */
string readFamilyList(list<FamilyMember *> fl){
   ostringstream outputString;
   outputString << fl.size();
   if(fl.size()){
     outputString << " ( ";
     list<FamilyMember*>::iterator i;
     for (i = fl.begin(); i != fl.end(); ++i)
     {
        outputString << (*i)->getName();
        outputString << " ";
     }
     outputString << ")";
   }
   return outputString.str();
}

int main(){
  ifstream inputFile;
  inputFile.open("tree.dat");
  FamilyMember * familytree = parseInputFile(inputFile);
  familytree->applyPreOrder( &printFamilyReport, familytree);
  familytree->applyPostOrder( &freeFamilyTree, familytree);
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

