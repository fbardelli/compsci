#include<list>
using namespace std;

class FamilyMember {
   string name;
   FamilyMember  *son;
   FamilyMember  *brother;
   FamilyMember  *parent;
   public:
     FamilyMember( string n ) :  name( n ), son( NULL ),
                                 brother( NULL ), parent(NULL){ }
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
     void addSon(FamilyMember * s);
     void addBrother(FamilyMember * b);
};

