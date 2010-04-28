#include <string>
#include <list>
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
  FamilyMember * yb = NULL;
  list<FamilyMember *> b = getBrothers();
  if(b.size() > 0){
    yb = b.back();
  }
  return yb;
}

FamilyMember * FamilyMember::getOldestBrother(){
  FamilyMember * ob = NULL;
  list<FamilyMember *> b = getBrothers();
  if(b.size() > 0){
    ob = b.front();
  }
  return ob;
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
    /* add brothers down the chain until there are none left */
    while(nextOldestSon != NULL){
      /* exclude self from list of brothers */
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
  /* get a list of oldest sons brothers, then add oldest son*/
  if (son){
    s = son->getBrothers();
    s.push_front(son);
  }
  return s;
}

void FamilyMember::addBrother(FamilyMember * b){
  FamilyMember * youngest = getYoungestBrother();
  /* Find brother with no brother pointer, and add*/
  if(youngest != NULL && youngest->getBrother() != this){
    youngest->setBrother(b);
  }else{
    setBrother(b);
  }
}

list<FamilyMember *> FamilyMember::getUncles(){
  if (parent !=NULL){
    return parent->getBrothers();
  }
  list<FamilyMember *> u;
  return u;
}

void FamilyMember::applyPreOrder( void(* func)(FamilyMember *), FamilyMember * m){
  /* apply passed in function in PreOrder to every node in the tree */
  func(m);
  if(m->getSon() != NULL){
    applyPreOrder(func,m->getSon());
  }
  if(m->getBrother() != NULL){
    applyPreOrder(func,m->getBrother());
  }
}

void FamilyMember::applyPostOrder( void(* func)(FamilyMember *), FamilyMember * m){
  /* apply passed in function in PostOrder to every node in the tree */
  if(m->getSon() != NULL){
    applyPostOrder(func,m->getSon());
  }
  if(m->getBrother() != NULL){
    applyPostOrder(func,m->getBrother());
  }
  func(m);
}
