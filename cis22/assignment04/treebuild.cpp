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

class Node {
   int data;
   Node  *left;
   Node  *right;
   Node  *parent;
   int   height;
   public:
     Node( int d ) : data( d ), left( NULL ), right( NULL ){ }
     Node( ) : data( NULL ), left( NULL ), right( NULL ){ parent = NULL; }
     int getData(){ return data; }
     void setData(int d){ data = d;}
     void insert(int d);
     void insert(Node * n);
     void remove(int d);
     void freeTree();
     void setParent(Node *p); 
     void traversePreOrder();
     void traverseInOrder();
     void traversePostOrder();
     void countNodes(int &i);
     void displayChildren();
};

void Node::insert(int d){
   insert( new Node(d) );
}

void Node::insert(Node * n){ 
  if (n->data == data){
    cout << "Node with value: " << data << " already exists\n";
  }
  if(n->data < data){
    if (left != NULL){
      left->insert(n);
    } else {
      left = n;
      left->setParent((Node *)this);
    }
  }else if ( n->data > data){
    if (right != NULL){
      right->insert(n);
    } else {
      right = n;
      right->setParent((Node *)this);
    }
  }
}

void Node::remove(int d){
  if(d < data){
    if (left != NULL){
      left->remove(d);
      return;
    } 
  } else if ( d > data) {
    if (right != NULL){
      right->remove(d);
      return;
    }  
  } else if (d == data){
    cout << "found " << d << " removing\n";
    if ( left != NULL && right != NULL){
      cout << d << " has L & R\n";

    }else if(left != NULL || right != NULL){
       Node *current = this;
       Node *replace;
       if(left !=NULL){
          cout << d << " has L\n";
          replace = left;
       }
       if(right !=NULL){
          cout << d << " has R\n";
          replace = right;
          cout << d << " assigned R\n";
       }
       if(parent != NULL){
         if( parent->right != NULL && parent->right == this){
           cout << d << " parent has me on R\n";
           parent->right = replace;
         }
         if(parent->left != NULL && parent->left == this){
           cout << d << " parent has me on L\n";
           parent->left = replace;
         }
       }
       cout<<"got here";
    }else{
       if(parent !=NULL){
         if(parent->right == this){
           parent->right = NULL;
         } else if(parent->left == this){
           parent->left = NULL;
         }
         delete this;
       }
       data = NULL;
    }
    return;
  }

  cout << "failed to remove " << d << "\n";
}

void Node::setParent(Node *p) { 
    parent = p;
}

void Node::traversePreOrder(){
   if(data){
     cout << data << " ";
   }
   if(left !=NULL){
     left->traversePreOrder();
   }
   if(right !=NULL){
     right->traversePreOrder();
   }
}

void Node::traverseInOrder(){
   if(left !=NULL){
     left->traverseInOrder();
   }
   if(data){
     cout << data << " ";
   }
   if(right !=NULL){
     right->traverseInOrder();
   }
}

void Node::traversePostOrder(){
   if(left !=NULL){
     left->traversePostOrder();
   }
   if(right !=NULL){
     right->traversePostOrder();
   }
   if(data){
     cout << data << " ";
   }
}

void Node::displayChildren(){
   int numChildren = 0;
   if(left !=NULL){
     numChildren++;
     left->displayChildren();
   }
   if(right !=NULL){
     numChildren++;
     right->displayChildren();
   }
   if(data){
     cout << "node #" << data << " has " << numChildren << " children\n";
   }
}


void Node::countNodes(int &i){
   if(data){
     i++;
   }
   if(left !=NULL){
     left->countNodes(i);
   }
   if(right !=NULL){
     right->countNodes(i);
   }
}

void Node::freeTree(){
   if(left !=NULL){
     left->freeTree();
   }
   if(right !=NULL){
     right->freeTree();
   }
   cout << "freeing node with data: " << data << endl;
   delete this;
}




Node * buildTree(list<int> numbers);
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
       cout << "\nTREE(Pre):";
       tree->traversePreOrder();
       cout << "\nTREE(In):";
       tree->traverseInOrder();
       cout << "\nTREE(Post):";
       tree->traversePostOrder();
       cout << "\n";
       int i = 0;
       tree->countNodes(i);
       tree->displayChildren();
       cout << "TREE(Count): " << i << "\n";
       processInsertsAndDeletes(in, tree);
       i = 0;
       tree->countNodes(i);
       tree->displayChildren();
       cout << "TREE(Count): " << i << "\n";
       tree->freeTree();
    }
    //pch = strtok (NULL, delimiter);
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
     //cout << "len:" << line.length() << endl;
  }
}

Node * buildTree(list<int> numbers){

}
