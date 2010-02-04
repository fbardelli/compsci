#include "point.h"
#define MAX_SIZE 100
/***************************************************
 * main
 **************************************************/

void initPolygon( point *polygon, int n );
void printPolygon( point *polygon, int n );

int main(int argc, char * argv[] ){
  assert(argc > 1);
  srand(time(NULL));
  int size = atoi(argv[1]);
  assert(size > 0);
  point *polygon = new point[size];
  initPolygon( polygon, size);
  cout << "Here are the points in your polygon\n";
  printPolygon( polygon, size);
  delete[] polygon;
  return 0;
}

void initPolygon( point *polygon, int n ){
  for ( int i = 0; i < n ; i ++){ 
    polygon[i].set((rand() % MAX_SIZE), (rand() % MAX_SIZE));
  }
}

void printPolygon( point *polygon, int n ){
  for ( int i = 0; i < n ; i ++){ 
    cout << "point #"<<i+1<<":";
    polygon[i].print();
    cout << endl;
  }
}
