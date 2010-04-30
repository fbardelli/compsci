#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void printArray( int array[], int size);
void bubbleSort( int array[], int size, int &comps, int &swaps);
void bubbleAnalyze(int array[], int size);
void quickSort(int array[], int left, int right, int &comps, int &swaps);
void quickAnalyze(int array[], int size);
void heapSort(int array[], int size, int &comps, int &swaps);
void siftDown(int array[], int root, int bottom, int &comps, int &swaps);
void heapAnalyze(int array[], int size);

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

void bubbleAnalyze(int array[], int size){
  int a[size];
  memcpy(a,array,sizeof(int)*size);
  int comps = 0;
  int swaps = 0;
  printArray( a, 10);
  bubbleSort( a, 10, comps, swaps);
  printArray( a, 10);
  cout << "comparisons:" << comps << " swaps:" << swaps <<endl;
}

void quickAnalyze(int array[], int size){
  int b[size];
  memcpy(b,array,sizeof(int)*size);
  int comps = 0;
  int swaps = 0;
  printArray( b, size);
  quickSort( b, 0, size-1, comps, swaps);
  printArray( b, size);
  cout << "comparisons:" << comps << " swaps:" << swaps <<endl;
}

void heapAnalyze(int array[], int size){
  int c[size];
  memcpy(c,array,sizeof(int)*size);
  int comps = 0;
  int swaps = 0;
  printArray( c, 10);
  heapSort( c, size, comps, swaps);
  printArray( c, 10);
  cout << "comparisons:" << comps << " swaps:" << swaps << endl;
}
 
int main(){
  cout <<"bubble\n";
  int random[10] = {2,4,5,6,1,9,8,7,3,0};
  int almostsorted[10] = {0,1,2,4,3,5,6,7,9,8};
  int reversed[10] = {9,8,7,6,5,4,3,2,1,0};
  bubbleAnalyze(random, 10);
  bubbleAnalyze(almostsorted, 10);
  bubbleAnalyze(reversed, 10);

  cout <<"\nquick\n";
  quickAnalyze(random, 10);
  quickAnalyze(almostsorted, 10);
  quickAnalyze(reversed, 10);

  cout <<"\nheap\n";
  heapAnalyze(random, 10);
  heapAnalyze(almostsorted, 10);
  heapAnalyze(reversed, 10);

  return 0;
}

