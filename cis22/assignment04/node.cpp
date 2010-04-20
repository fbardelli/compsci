#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;
#include <sstream> // header file for string stream processing
using std::ostringstream; // stream insertion operators

#include "node.h"

void Node::insert(int d){
   /* helper method so caller need not worry about allocating memory on insert*/
   insert( new Node(d) );
}

void Node::insert(Node * n) { 
 /*  Traverse tree until approriate spot is found 
 *   Using a simple left = less than, right = greater than
 *   Will not balance well with pre-sorted data
 * */
  if (n->data == data){
    /* print error if node is in the tree */
    cout << "Failed to insert Node with value=" << data << " Node already exists\n";
  }
  if(n->data < data){
    if (left != NULL){
      left->insert(n);
    } else {
      left = n;
      left->setParent(this);
    }
  }else if ( n->data > data){
    if (right != NULL){
      right->insert(n);
    } else {
      right = n;
      right->setParent(this);
    }
  }
}


void Node::remove(int d){
 /*  Traverse tree moving right or left 
 *   until we reach the leaf we are seeking */
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
    /* found the leaf, there are three posible cases to deal with */ 
    if ( left != NULL && right != NULL){
       /* both right and left are filled 
        * find leftmost node (node with lowest value in right tree) 
        * on the right side, replace current value with that value
        * then remove that value from the right tree.
        */ 
       Node * replacement = right;
       while (replacement->left != NULL){
         replacement = replacement->left;
       }
       data = replacement->data;
       /* remove node with duplicate data in right tree */
       right->remove(data);
    }else if(left != NULL || right != NULL){
       /* if we have exactly one child, 
        * replace this node with its child
        */
       Node *replace;
       if(left !=NULL){
          replace = left;
       }
       if(right !=NULL){
          replace = right;
       }
       data = replace->data;
       right = replace->right;
       left = replace->left;
       /* relevant node data copied, free it */
       delete replace;
    }else{
       /* if this node has no children 
        * set references in our parent to null
        * and simply delete this node
       */
       if(parent !=NULL){
         if(parent->right == this){
           parent->right = NULL;
         } else if(parent->left == this){
           parent->left = NULL;
         }
         delete this;
       }else{
         empty = true;
       }
       data = NULL;
    }
    return;
  }
  /* If we get here we traversed the tree without finding the requested node */
  cout << "failed to remove " << d << " Node not found\n";
}

void Node::setParent(Node *p) { 
    parent = p;
}

void Node::traversePreOrder(){
   /* preorder = root, left, right */
   if(!empty)
     cout << data << " ";
   if(left !=NULL){
     left->traversePreOrder();
   }
   if(right !=NULL){
     right->traversePreOrder();
   }
}

void Node::traverseInOrder(){
   /* inorder = left, root, right */
   if(left !=NULL){
     left->traverseInOrder();
   }
   if(!empty)
     cout << data << " ";
   if(right !=NULL){
     right->traverseInOrder();
   }
}

void Node::traversePostOrder(){
   /* postorder = left, right, root */
   if(left !=NULL){
     left->traversePostOrder();
   }
   if(right !=NULL){
     right->traversePostOrder();
   }
   if(!empty)
     cout << data << " ";
}

void Node::displayChildren(){
  /* traverse tree displaying # children for each node*/
  int numChildren = 0;
  ostringstream children;
  if(left !=NULL){
    numChildren++;
    children << "left:" << left->data;
    left->displayChildren();
  }
  if(right !=NULL){
    numChildren++;
    if(left!=NULL){
      children <<",";
    }
    children << "right:" << right->data;
    right->displayChildren();
  }
  if(!empty){
    cout << "node #" << data << " has " << numChildren << " child" << (numChildren == 1 ? "":"ren" );
    if(numChildren){
      cout << " (" << children.str() << ")";
    }
    cout << endl;
  }
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
   /* traverse tree updating i with total nodes in tree*/
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
   /* traverse tree postorder freeing nodes from the bottom up*/
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

