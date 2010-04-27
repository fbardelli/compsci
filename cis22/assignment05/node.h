#include<list>
class Node {
   int remainingSons;
   string name;
   Node  *son;
   Node  *brother;
   Node  *parent; 
   public:
     Node( string n, int numSons ) :  name( n ), remainingSons(numSons), son( NULL ), 
                                      brother( NULL ), parent(NULL){ }
     int getRemainingSons(){ return remainingSons; }
     string getName(){ return name;}
     Node * getParent(){return parent;}
     Node * getYoungestBrother();
     Node * getOldestBrother();
     std::list<Node *> getBrothers();
     void setParent(Node * p){ parent = p;}
     void setBrother(Node * b){ brother = b;}
     void addSon(string n, int numSons);
     void addBrother(string n, int numSons);
};

