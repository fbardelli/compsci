#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;


#include "node.h"

void Node::insert(int d){
   insert( new Node(d) );
}

void Node::insert(Node * n){ 
  if (n->data == data){
    cout << "Failed to insert Node with value:" << data << " Node already exists\n";
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
    if ( left != NULL && right != NULL){
       Node * replacement = right;
       while (replacement->left != NULL){
         replacement = replacement->left;
       }
       data = replacement->data;
       replacement->remove(data);
    }else if(left != NULL || right != NULL){
       Node *current = this;
       Node *replace;
       if(left !=NULL){
          replace = left;
       }
       if(right !=NULL){
          replace = right;
       }
       if(parent != NULL){
         if( parent->right != NULL && parent->right == this){
           parent->right = replace;
         }
         if(parent->left != NULL && parent->left == this){
           parent->left = replace;
         }
       }
       if(replace != NULL){
           replace->setParent(parent);
       }
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

  cout << "failed to remove " << d << " Node not found\n";
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
  cout << "node #" << data << " has " << numChildren << " children\n";
}
void Node::countReport(){
  int i = countNodes();
  cout << "TREE(Count): " << i << "\n";
}

int Node::countNodes(){
  int i = 0;
  countNodes(i);
  return i;
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

void Node::traversalReport(){
  cout << "TREE(Pre):";
  traversePreOrder();
  cout << "\nTREE(In):";
  traverseInOrder();
  cout << "\nTREE(Post):";
  traversePostOrder();
  cout << "\n";
}


