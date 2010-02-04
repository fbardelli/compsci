#include "point.h"
#define MAX_SIZE 100
/***************************************************
 * main
 **************************************************/
class polygon {
  private:
    int size;
    point *points;
  public:
    polygon( int n );
    ~polygon();
    void init();
    void print();
};

polygon::polygon(int n){
  size = n;
  points = new point[size];
}

polygon::~polygon(){
  delete[] points;
}

void polygon::init(){
  for ( int i = 0; i < size ; i ++){ 
    points[i].set((rand() % MAX_SIZE), (rand() % MAX_SIZE));
  }
}
void polygon::print(){
  for ( int i = 0; i < size ; i ++){ 
    cout << "point #"<<i+1<<":";
    points[i].print();
    cout << endl;
  }
}

int main(int argc, char * argv[] ){
  assert(argc > 1);
  srand(time(NULL));
  int size = atoi(argv[1]);
  assert(size > 0);
  polygon p(size);
  p.init();
  cout << "Here are the points in your polygon\n";
  p.print();
  return 0;
}

