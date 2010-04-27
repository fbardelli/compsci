#include <string>
#include <list>
using namespace std;
#include "node.h"

void Node::addSon(string n, int numSons){
  if( son == NULL){
    son = new Node(n, numSons);
    son->setParent(this);
  }else{
    son->addBrother(n,numSons);
    Node * youngestBrother = son->getYoungestBrother();
    youngestBrother->setParent(this);
  }
}

Node * Node::getYoungestBrother(){
  Node * youngest = this;
  while( youngest->brother != NULL){
    youngest = youngest->brother;
  }
  return youngest;
}

Node * Node::getOldestBrother(){
  Node * parent = getParent();
  return parent->son;
}

list<Node *> Node::getBrothers(){
  list<Node *> b;
  Node * parent = getParent();
  b.push_back(parent->son);
  return b;
}

void Node::addBrother(string n, int numSons){
  Node * youngest = getYoungestBrother();
  youngest->setBrother(new Node(n, numSons));
}
