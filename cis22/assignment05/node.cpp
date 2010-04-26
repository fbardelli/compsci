#include <string>
using namespace std;
#include "node.h"

void Node::addSon(string n, int numSons){
  if( son == NULL){
    son = new Node(n, numSons);
    son->setParent(this);
  }else{
    son->addBrother(n,numSons);
    Node * youngestBrother = son->youngestBrother();
    youngestBrother->setParent(this);
  }
}

Node * Node::youngestBrother(){
  Node * youngest = this;
  while( youngest->brother != NULL){
    youngest = youngest->brother;
  }
  return youngest;
}

void Node::addBrother(string n, int numSons){
  Node * youngest = youngestBrother();
  youngest->setBrother(new Node(n, numSons));
}
