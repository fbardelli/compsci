#include <string>
#include <list>
#include <iostream>
using namespace std;
#include "family.h"

void FamilyMember::addSon(FamilyMember * s){
  if( son == NULL){
    son = s;
    son->setParent(this);
  }else{
    son->addBrother(s);
    FamilyMember * youngestBrother = son->getYoungestBrother();
    youngestBrother->setParent(this);
  }
}

FamilyMember * FamilyMember::getGrandparent(){
  if(parent !=NULL){
    return parent->getParent();
  }
}

FamilyMember * FamilyMember::getYoungestBrother(){
  FamilyMember * youngest = this;
  while( youngest->brother != NULL){
    youngest = youngest->brother;
  }
  return youngest;
}

FamilyMember * FamilyMember::getOldestBrother(){
  if (parent != NULL){
    return parent->getSon();
  }else{
    return this;
  }
}

FamilyMember * FamilyMember::getOldestSon(){
  return son;
}

FamilyMember * FamilyMember::getYoungestSon(){
  if(son){
    return son->getYoungestBrother();
  }
}

list<FamilyMember *> FamilyMember::getBrothers(){
  list<FamilyMember *> b;
  FamilyMember * parent = getParent();
  if(parent != NULL){
    FamilyMember * nextOldestSon = parent->getOldestSon();
    while(nextOldestSon != NULL){
      if(nextOldestSon != this){
        b.push_back(nextOldestSon);
      }
      nextOldestSon = nextOldestSon->brother;
    }
  }
  return b;
}

list<FamilyMember *> FamilyMember::getSons(){
  list<FamilyMember *> s;
  if (son){
    s = son->getBrothers();
    s.push_front(son);
  }
  return s;
}

void FamilyMember::addBrother(FamilyMember * b){
  FamilyMember * youngest = getYoungestBrother();
  youngest->setBrother(b);
}


list<FamilyMember *> FamilyMember::getUncles(){
  if (parent !=NULL){
    return parent->getBrothers();
  }
  list<FamilyMember *> u;
  return u;
}


void FamilyMember::applyPreOrder( void(* func)(FamilyMember *), FamilyMember * m){
  func(m);
  if(m->getSon() != NULL){
    applyPreOrder(func,m->getSon());
  }
  if(m->getBrother() != NULL){
    applyPreOrder(func,m->getBrother());
  }
}
