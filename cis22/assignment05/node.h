class Node {
   int remainingSons;
   string name;
   Node  *sons;
   Node  *brothers;
   Node  *parent; //parent or brother
   public:
     Node( string n, int numSons ) :  name( n ), remainingSons(numSons), sons( NULL ), 
                                      brothers( NULL ), parent(NULL){ }
     int getRemainingSons(){ return remainingSons; }
     void getName(){ return name}
     Node * getParent{
       return parent;
     }
     void setParent(Node * p){ parent = p};
     void insertSon(string n, int numSons);
     void freeTree();
/*     void traversePreOrder();
     void traverseInOrder();
     void traversePostOrder();
     void countReport();
     void countNodes(int &i);
     int  countNodes();
     void displayChildren();
     void traversalReport();
*/
};

