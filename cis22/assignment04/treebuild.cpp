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


int main(){

  ifstream inputFile;
  inputFile.open("sets.dat");
  processData(inputFile);
  return 0;
}


void processData( ifstream& in ){

  string line, parts[3];
  while (getline(in,line) && ! in.eof()){

    //const char * delimiter = "\t";
    //char * pch = strtok((char *)line.c_str(),delimiter);
    //pch = strtok (NULL, delimiter);
  }
}

Node * buildTree(list<int> numbers){

}
