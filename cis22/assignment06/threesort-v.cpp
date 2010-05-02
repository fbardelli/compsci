#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
using namespace std;
#define HEAP 'h'
#define BUBBLE 'b'
#define QUICK 'q'

void printArray( vector <int> array, int size);
void bubbleSort( vector <int> & array, int size, int &comps, int &swaps);
void quickSort(vector <int> & array, int left, int right, int &comps, int &swaps);
void heapSort(vector <int> & array, int size, int &comps, int &swaps);
void siftDown(vector <int> & array, int root, int bottom, int &comps, int &swaps);
void sortAnalyze(vector <int> array, int size, char type);
void threeSort(vector<int> & random, vector<int> & almostsorted, vector<int> & reversed, int size, char type);
void runSorts(int size);
vector<int>  makeReversed(int size);
vector<int> makeSorted(int size);
vector<int> makeAlmostSorted(int size);
vector<int> makeRandom( int size );

void printArray(vector<int> array, int size){
  for(int i = 0; i < size; i++){
    cout << array[i] << " ";
  }
  cout << "\n";
}

void bubbleSort(vector<int> & array, int size, int &comps, int &swaps){
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

void quickSort(vector<int> & array, int left, int right, int &comps, int &swaps) {
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
                  swaps++; comps++;
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

void heapSort(vector<int> & array, int size, int &comps, int &swaps) {
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
 
 
void siftDown(vector<int> & array, int root, int bottom, int &comps, int &swaps) {
  int done, maxChild, temp;
  done = 0;
  while ((root*2 <= bottom) && (!done)){
    if (root*2 == bottom){
      maxChild = root * 2;
      comps+=1;
    }else if (array[root * 2] > array[root * 2 + 1]){
      maxChild = root * 2;
      comps+=2;
    }else{
      maxChild = root * 2 + 1;
      comps+=2;
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

void sortAnalyze(vector<int> array, int size, char type){
  vector<int> a;
  int comps = 0;
  int swaps = 0;
  a = array;
  cout << "pre sort: ";
  printArray( a, size);
  /* run sort specified counting comparisons and swaps */
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
  cout << "post sort: ";
  printArray( a, size);
  cout << "comparisons: " << comps << " swaps: " << swaps <<endl;
}

vector <int> makeReversed(int size){
  vector <int> array;
  for(int i = 0; i <= size; i++){
    array.push_back(size-(i+1));
  }
  return array;
}

vector <int> makeSorted(int size){
  vector <int> array;
  for(int i = 0; i <= size; i++){
    array.push_back(i);
  }
  return array;
}
 
vector <int> makeAlmostSorted(int size){
  vector <int> array = makeSorted(size);
  /* swap around 1/5th of the elements in the array
    with the next element over 
  */
  for(int i = 0; i <= size/5; i++){
    int randomIndex = (rand() % size);
    int temp = array[randomIndex];
    int swapIndex;
    if(randomIndex == size-1){
      swapIndex= randomIndex-1;
    }else{
      swapIndex= randomIndex+1;
    }
    array[randomIndex] =  array[swapIndex];
    array[swapIndex] = temp;
  }
  return array;
}

vector <int> makeRandom( int size ) {
  vector <int> array = makeSorted(size);
  for (int i = 0; i < size; i++) {
     int temp = array[i];
     int randomIndex = (rand() % (size-i))+i;
     array[i] =  array[randomIndex];
     array[randomIndex] = temp;
  }
  return array;
}

void threeSort(vector<int> & random, vector<int> & almostsorted, vector<int> & reversed, int size, char type){
  cout << "random\n";
  sortAnalyze(random, size, type);
  cout << "almost sorted\n";
  sortAnalyze(almostsorted, size, type);
  cout << "reversed\n";
  sortAnalyze(reversed, size, type);
}

void runSorts(int size){
  vector<int> random = makeRandom(size); 
  vector<int> reversed = makeReversed(size);
  vector<int> almostsorted = makeAlmostSorted(size);
  cout <<"\nbubble sort of " << size <<" items\n";
  threeSort(random,almostsorted,reversed,size,BUBBLE);

  cout <<"\nquick sort of " << size <<" items\n";
  threeSort(random,almostsorted,reversed,size,QUICK);

  cout <<"\nheap sort of " << size <<" items\n";
  threeSort(random,almostsorted,reversed,size,HEAP);

}

int main(){
  /* initialize random number generator */
  struct timeval time; 
  gettimeofday(&time, 0);
  long int s = time.tv_usec * getpid(); 
  srand(s);

  /* run 3 different sorts on each of 3 number sets */
  runSorts(10);
  runSorts(50);
  runSorts(100);

  return 0;
}

