#include "point.h"
#define MAX_SIZE 100
/***************************************************
 * main
 **************************************************/

int main(int argc, char * argv[] ){
  assert(argc > 1);
  srand(time(NULL));
  int size = atoi(argv[1]);
  assert(size > 0);
  point *polygon = new point[size];
  cout << "Here are the points in your polygon\n";
  for ( int i = 0; i < size; i ++){ 
    polygon[i].set((rand() % MAX_SIZE), (rand() % MAX_SIZE));
    cout << "point #"<<i+1<<":";
    polygon[i].print();
    cout << endl;
  }
  delete[] polygon;
  return 0;
}

