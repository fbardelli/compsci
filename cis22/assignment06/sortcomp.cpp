#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;
#define HEAP 'h'
#define BUBBLE 'b'
#define QUICK 'q'

void printArray( int array[], int size);
void bubbleSort( int array[], int size, int &comps, int &swaps);
void quickSort(int array[], int left, int right, int &comps, int &swaps);
void heapSort(int array[], int size, int &comps, int &swaps);
void siftDown(int array[], int root, int bottom, int &comps, int &swaps);
void sortAnalyze(int array[], int size, char type);
void threeSort(int random[], int almostsorted[], int reversed[], int size, char type);
void runSorts(int size);
int * makeReversed(int size);
int * makeSorted(int size);
int * makeAlmostSorted(int size);
int * makeRandom( int size );

void printArray( int array[], int size){
  for(int i = 0; i < size; i++){
    cout << array[i] << " ";
  }
  cout << "\n";
}

void bubbleSort( int array[], int size, int &comps, int &swaps){
  bool swapped = true;
  while(swapped){
    swapped = false;
    for(int i = 0; i < size - 1; i++){
      comps++;
      if(array[i] > array[i+1]){
         swaps++;
         int temp = array[i];
         array[i] = array[i+1];
         array[i+1] = temp;
         swapped = true;
      }
    }
  }
}

void quickSort(int array[], int left, int right, int &comps, int &swaps) {
      int i = left, j = right;
      int tmp;
      int pivot = array[(left + right) / 2];
 
      /* partition */
      while (i <= j) {
            while (array[i] < pivot)
                  i++; comps++;
            while (array[j] > pivot)
                  j--; comps++;
            if (i <= j) {
                  swaps++;
                  tmp = array[i];
                  array[i] = array[j];
                  array[j] = tmp;
                  i++;
                  j--;
            }
      }

      /* recursion */
      if (left < j)
            quickSort(array, left, j, ++comps,swaps);
      if (i < right)
            quickSort(array, i, right, ++comps,swaps);
}

void heapSort(int array[], int size, int &comps, int &swaps) {
  int i, temp;
  for (i = size - 1; i >= 0; i--)
    siftDown(array, i, size - 1, comps, swaps);
 
  for (i = size-1; i >= 1; i--){
    swaps++;
    temp = array[0];
    array[0] = array[i];
    array[i] = temp;
    siftDown(array, 0, i-1, comps, swaps);
  }
}
 
 
void siftDown(int array[], int root, int bottom, int &comps, int &swaps) {
  int done, maxChild, temp;
  done = 0;
  while ((root*2 <= bottom) && (!done)){
    if (root*2 == bottom){
      maxChild = root * 2;
      comps++;
    }else if (array[root * 2] > array[root * 2 + 1]){
      maxChild = root * 2;
      comps++;
    }else{
      maxChild = root * 2 + 1;
    }

    if (array[root] < array[maxChild]){
      comps++;
      swaps++;
      temp = array[root];
      array[root] = array[maxChild];
      array[maxChild] = temp;
      root = maxChild;
    }
    else
      done = 1;
  }
}

void sortAnalyze(int array[], int size, char type){
  int * a = new int[size];
  memcpy(a,array,sizeof(int)*size);
  int comps = 0;
  int swaps = 0;
  printArray( a, size);
  switch(type){
    case BUBBLE:
      bubbleSort( a, size, comps, swaps);
      break;
    case QUICK:
      quickSort( a, 0, size-1, comps, swaps);
      break;
    case HEAP:
      heapSort( a, size, comps, swaps);
      break;
  }
  printArray( a, size);
  cout << "comparisons:" << comps << " swaps:" << swaps <<endl;
  delete [] a;
}

int * makeReversed(int size){
  int * array = new int[size];
  for(int i = 0; i <= size; i++){
    array[i] = size-(i+1);
  }
  return array;
}

int * makeSorted(int size){
  int * array = new int[size];
  for(int i = 0; i <= size; i++){
    array[i] = i;
  }
  return array;
}
 
int * makeAlmostSorted(int size){
  int * array = makeSorted(size);
  for(int i = 0; i <= size/5; i++){
    int randomIndex = (rand() % size);
    int temp = array[randomIndex];
    int swapIndex;
    if(randomIndex == size){
      swapIndex= randomIndex-1;
    }else{
      swapIndex= randomIndex+1;
    }
    array[randomIndex] =  array[swapIndex];
    array[swapIndex] = temp;
  }
  return array;
}

int * makeRandom( int size ) {
  int * array = makeSorted(size);

  for (int i = 0; i < size; i++) {
     int temp = array[i];
     int randomIndex = (rand() % (size-i))+i;
     array[i] =  array[randomIndex];
     array[randomIndex] = temp;
  }
  return array;
}

void threeSort(int random[], int almostsorted[], int reversed[],int size, char type){
  cout << "random\n";
  sortAnalyze(random, size, type);
  cout << "almost sorted\n";
  sortAnalyze(almostsorted, size, type);
  cout << "reversed\n";
  sortAnalyze(reversed, size, type);
}

void runSorts(int size){
  int * random = makeRandom(size); 
  int * reversed = makeReversed(size);
  int * almostsorted = makeAlmostSorted(size);
  cout <<"\nbubble sort of " << size <<" items\n";
  threeSort(random,almostsorted,reversed,size,BUBBLE);

  cout <<"\nquick sort of " << size <<" items\n";
  threeSort(random,almostsorted,reversed,size,QUICK);

  cout <<"\nheap sort of " << size <<" items\n";
  threeSort(random,almostsorted,reversed,size,HEAP);
  delete [] reversed;
  delete [] random;
}

int main(){

  struct timeval time; 
  gettimeofday(&time, 0);
  long int s = time.tv_usec * getpid(); 
  srand(s);
  runSorts(10);
  runSorts(50);
  runSorts(100);

  return 0;
}

