#include<list>
using namespace std;

class FamilyMember {
   int remainingSons;
   string name;
   FamilyMember  *son;
   FamilyMember  *brother;
   FamilyMember  *parent;
   public:
     FamilyMember( string n, int numSons ) :  name( n ), remainingSons(numSons), son( NULL ),
                                      brother( NULL ), parent(NULL){ }
     int getRemainingSons(){ return remainingSons; }
     string getName(){ return name;}
     FamilyMember * getParent(){return parent;}
     FamilyMember * getGrandparent();
     FamilyMember * getYoungestBrother();
     FamilyMember * getOldestBrother();
     FamilyMember * getYoungestSon();
     FamilyMember * getOldestSon();
     list<FamilyMember *> getBrothers();
     list<FamilyMember *> getSons();
     list<FamilyMember *> getUncles();
     void setParent(FamilyMember * p){ parent = p;}
     void setBrother(FamilyMember * b){ brother = b;}
     void addSon(string n, int numSons);
     void addBrother(string n, int numSons);
};

