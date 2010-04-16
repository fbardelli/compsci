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

#define RECORD_TERMINATOR -999

struct Node {
   int data;
   Node  *left;
   Node  *right;
   Node  *parent;
   int   height;
   Node( int d, Node *lt = NULL, Node *rt=NULL ) : data( d ), left( lt ), right( rt ){}
   void insert(Node * n){ 
     if (n->data == data){
       cout << "Node with value: " << data << " already exists\n";
     }
     if(n->data < data){
       if (left != NULL){
         left->insert(n);
       } else {
         left = n;
       }
     }else if ( n->data > data){
       if (right != NULL){
         right->insert(n);
       } else {
         right = n;
       }
     }
   }
   void traversePreOrder(){
      cout << data << " ";
      if(left !=NULL){
        left->traversePreOrder();
      }
      if(right !=NULL){
        right->traversePreOrder();
      }
   }
   void traverseInOrder(){
      if(left !=NULL){
        left->traverseInOrder();
      }
      cout << data << " ";
      if(right !=NULL){
        right->traverseInOrder();
      }
   }
   void traversePostOrder(){
      if(left !=NULL){
        left->traversePostOrder();
      }
      if(right !=NULL){
        right->traversePostOrder();
      }
      cout << data << " ";
   }
   void countNodes(int &i){
      i++;
      if(left !=NULL){
        left->countNodes(i);
      }
      if(right !=NULL){
        right->countNodes(i);
      }
   }

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
       int number =   atoi(pch);
       Node * tree = new Node(number,NULL,NULL);
       while(number != RECORD_TERMINATOR ){
         nodes.push_back(number);
         pch = strtok (NULL, delimiter);
         number = atoi(pch);
         if(number != RECORD_TERMINATOR){
           Node * node = new Node(number,NULL,NULL);
           tree->insert(node);
         }
       }
       for(list<int>::iterator current = nodes.begin();current != nodes.end(); ++current){
         cout << (*current) << ":";
       }
       cout << "\n  =" << nodes.size()<<"\n";
       cout << "\nTREE(Pre):";
       tree->traversePreOrder();
       cout << "\nTREE(In):";
       tree->traverseInOrder();
       cout << "\nTREE(Post):";
       tree->traversePostOrder();
       cout << "\n";
       int i = 0;
       tree->countNodes(i);
       cout << "TREE(Count): " << i << "\n";
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
     const char * delimiter = "\t";
     char * pch = strtok((char *)line.c_str(),delimiter);

     cout << "len:" << line.length() << endl;
  }
}

Node * buildTree(list<int> numbers){

}
