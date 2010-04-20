class Node {
   int data;
   Node  *left;
   Node  *right;
   Node  *parent;
   int   height;
   public:
     Node( int d ) : data( d ), left( NULL ), right( NULL ), parent(NULL){ }
     Node( ) : data( NULL ), left( NULL ), right( NULL ){ parent = NULL; }
     int getData(){ return data; }
     void setData(int d){ data = d;}
     void insert(int d);
     void insert(Node * n);
     void remove(int d);
     void freeTree();
     void setParent(Node *p); 
     void traversePreOrder();
     void traverseInOrder();
     void traversePostOrder();
     void countReport();
     void countNodes(int &i);
     int  countNodes();
     void displayChildren();
     void traversalReport();
};

