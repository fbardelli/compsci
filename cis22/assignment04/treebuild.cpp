/*  Frank Bardelli
 *  CIS 22 Data Structures
 *  Assignment #3
 *  March 31, 2010
 */
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstring>
#include<list>
#define MARKUP 1.3f
using namespace std;
#include <sstream> // header file for string stream processing
using std::ostringstream; // stream insertion operators

struct Node {
   int data;
   Node  *left;
   Node  *right;
   Node  *parent;
   int   height;
   Node( int d, Node *lt, Node *rt ) : data( d ), left( lt ), right( rt ){}
};

Node * buildTree(list<int> numbers);
void processData( ifstream& in );
void processInsertsAndDeletes( ifstream& in, list<int> numbers );


int main(){

  ifstream inputFile;
  inputFile.open("sets.dat");
  processData(inputFile);
  return 0;
}


void processData( ifstream& in ){

  string line;
  while (getline(in,line) && ! in.eof()){
    if(line.find("SET") == 0){
       list<int> nodes;
       string numbers = line.substr(line.find(':')+2);
       const char * delimiter = " ";
       char * pch = strtok((char *)numbers.c_str(),delimiter);
         
       nodes.push_back(atoi(pch));
       while(pch = strtok (NULL, delimiter)){
         nodes.push_back(atoi(pch));
       }
       for(list<int>::iterator current = nodes.begin();current != nodes.end(); ++current){
         cout << (*current) << ":";
       }
       cout << "\n  =" << nodes.size()<<"\n";
       processInsertsAndDeletes(in, nodes);
    }
    //pch = strtok (NULL, delimiter);
  }
}

void processInsertsAndDeletes( ifstream& in, list<int> numbers ){
  string line;
  while (getline(in,line) && ! in.eof()){
     if (line.length() == 0){
       break;
     }
     cout << "len:" << line.length() << endl;
  }
}

Node * buildTree(list<int> numbers){

}
