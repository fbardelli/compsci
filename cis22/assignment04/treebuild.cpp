/*  Frank Bardelli
 *  CIS 22 Data Structures
 *  Assignment #3
 *  March 31, 2010
 */
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstring>
using namespace std;

#define RECORD_TERMINATOR -999

#include "node.h"


void processData( ifstream& in );
void processInsertsAndDeletes( ifstream& in, Node * tree );


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
       string numbers = line.substr(line.find(':')+2);
       const char * delimiter = " ";
       char * pch = strtok((char *)numbers.c_str(),delimiter);
       int number; 
       Node * tree = new Node(); 
       while( (number = atoi(pch) ) != RECORD_TERMINATOR ){
         if(! tree->getData()){
           tree->setData(number);
         }else{
           tree->insert(number);
         }
         pch = strtok (NULL, delimiter);
       }

       tree->traversalReport();
       tree->countReport();
       tree->displayChildren();
       
       processInsertsAndDeletes(in, tree);

       tree->traversalReport();
       tree->countReport();
       tree->displayChildren();
       
       tree->freeTree();
       cout << "\n";
    }
  }
}

void processInsertsAndDeletes( ifstream& in, Node * tree ){
  string line;
  while (getline(in,line) && ! in.eof()){
     if (line.length() == 0){
       break;
     }
     const char * delimiter = "\t";
     char * pch = strtok((char *)line.c_str(),delimiter);
     string op;
     string insert_key = "INSERT ";
     string delete_key = "DELETE ";
     while( pch != NULL){
        op = string(pch);
        cout << op << endl;
        if(op.find(insert_key) != -1){
          tree->insert( atoi( op.substr( insert_key.length() ).c_str()) );
        }else if (op.find(delete_key) != -1){
          tree->remove( atoi( op.substr( delete_key.length() ).c_str()) );
        }
        pch = strtok (NULL, delimiter);
     }
  }
}

