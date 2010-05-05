#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
#include <map>
using namespace std;
#define BUBBLE 'b'
#define QUICK  'q'
#define HEAP   'h'

struct SortPerformance {
  char type;
  int swaps;
  int comps;
  SortPerformance():swaps(0),comps(0){}
};

/* switched from dynamic arrays to STL vector<int>, as the copy behavior
   for vectors is simple, performance difference is negligible
   and there is much less memory mgmt overhead */
class SortCompare {
  private:
    int comps, swaps, size;
    string listType;
    vector<int> array;
    map<char,string> sortDesc;
  public:
    SortCompare(int s, string lt, vector<int> a): size(s),array(a),listType(lt){
      sortDesc[BUBBLE] = "BubbleSort";
      sortDesc[QUICK] = "QuickSort";
      sortDesc[HEAP] = "HeapSort";
    };
    void sortReport(vector<SortPerformance> sp);
    void printArray( vector <int> & array, int size);
    void bubbleSort( vector <int> & array, int size);
    void quickSort(vector <int> & array, int left, int right);
    void heapSort(vector <int> & array, int size);
    void siftDown(vector <int> & array, int root, int bottom);
    SortPerformance sortAnalyze(char type);
    void runSorts();
};

vector<int> makeReversed(int size);
vector<int> makeSorted(int size);
vector<int> makeAlmostSorted(int size);
vector<int> makeRandom( int size );

void SortCompare::printArray(vector<int> & array, int size){
  for(int i = 0; i < size; i++){
    cout << array[i] << " ";
  }
  cout << "\n";
}

void SortCompare::bubbleSort(vector<int> & array, int size){
  bool swapped = true;
  while(swapped){
    swapped = false;
    /* if we get through the list with no swaps we're done */
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

void SortCompare::quickSort(vector<int> & array, int left, int right) {
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
      if (left < j){
        comps++;
        quickSort(array, left, j);
      }
      if (i < right){
        comps++;
        quickSort(array, i, right);
      }
}

void SortCompare::heapSort(vector<int> & array, int size) {
  int i, temp;
  for (i = size - 1; i >= 0; i--)
    siftDown(array, i, size - 1);
 
  for (i = size-1; i >= 1; i--){
    swaps++;
    temp = array[0];
    array[0] = array[i];
    array[i] = temp;
    siftDown(array, 0, i-1);
  }
}
 
 
void SortCompare::siftDown(vector<int> & array, int root, int bottom) {
  int done, maxChild, temp;
  done = 0;
  while ((root*2 <= bottom) && (!done)){
    if (root*2 == bottom){
      maxChild = root * 2;
    }else if (array[root * 2] > array[root * 2 + 1]){
      maxChild = root * 2;
      comps++;
    }else{
      maxChild = root * 2 + 1;
      comps++;
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

SortPerformance SortCompare::sortAnalyze(char type){
  SortPerformance sp;
  vector<int> a;
  a.reserve(size);
  comps = 0;
  swaps = 0;
  /* deep copy of vector data so we get a copy to sort*/
  a = array;
  cout << "pre sort: ";
  printArray( a, size);
  /* run sort specified counting comparisons and swaps */
  switch(type){
    case BUBBLE:
      bubbleSort( a, size );
      break;
    case QUICK:
      quickSort( a, 0, size-1 );
      break;
    case HEAP:
      heapSort( a, size );
      break;
  }
  /* show the results of the sort */
  cout << "post sort: ";
  printArray( a, size);
  cout << "comparisons: " << comps << " swaps: " << swaps <<endl;
  /* fill in data about performance to compare aganst other sorts */
  sp.comps = comps;
  sp.swaps = swaps;
  sp.type  = type;
  return sp;
}


void SortCompare::runSorts(){
  vector <SortPerformance> sp; 
  cout <<"\nbubble sort of " << size << " " << listType << " items\n";
  sp.push_back(sortAnalyze(BUBBLE));

  cout <<"\nquick sort of " << size << " " << listType << " items\n";
  sp.push_back(sortAnalyze(QUICK));

  cout <<"\nheap sort of " << size << " " << listType << " items\n";
  sp.push_back(sortAnalyze(HEAP));
  /* compare stats from all three sort types */
  sortReport(sp);
}

void SortCompare::sortReport(vector<SortPerformance> sp){
  SortPerformance mostComps, leastComps, midComps, 
                  mostSwaps, leastSwaps, midSwaps;
  /*determine best, worst and middle sorts by comparisons and
    interchanges (swaps) */
  for(int i=0; i<sp.size(); i++){
    if(sp[i].comps > mostComps.comps)
      mostComps=sp[i];
    if( leastComps.comps == 0 || sp[i].comps < leastComps.comps )
      leastComps=sp[i];
    if(sp[i].swaps > mostSwaps.swaps)
      mostSwaps=sp[i];
    if( leastSwaps.swaps == 0 || sp[i].swaps < leastSwaps.swaps )
      leastSwaps=sp[i];
  }
  for(int i=0; i<sp.size(); i++){
    if(sp[i].type != mostComps.type && sp[i].type != leastComps.type)
      midComps = sp[i];
    if(sp[i].type != mostSwaps.type && sp[i].type != leastSwaps.type)
      midSwaps = sp[i];
  }
  
  cout << "\nfor a " << listType << " list of " << size << " items:\n"
       << " The Most Comparisons occur with " << sortDesc[mostComps.type] 
       << " with " << mostComps.comps << endl
       << " The Middle number of Comparisons occur with " << sortDesc[midComps.type] 
       << " with " << midComps.comps << endl
       << " The Least Comparisons occur with " << sortDesc[leastComps.type]  
       << " with " << leastComps.comps << endl
       << " The Most Swaps occur with " << sortDesc[mostSwaps.type] 
       << " with " << mostSwaps.swaps << endl
       << " The Middle number of Swaps occur with " << sortDesc[midSwaps.type] 
       << " with " << midSwaps.swaps << endl
       << " The Least Swaps occur with " << sortDesc[leastSwaps.type]  
       << " with " << leastSwaps.swaps << endl;



}

vector <int> makeReversed(int size){
  vector <int> array;
  /* give  vector a hint on how much memory to allocate */
  array.reserve(size);
  for(int i = 0; i <= size; i++){
    array.push_back(size-(i+1));
  }
  return array;
}

vector <int> makeSorted(int size){
  vector <int> array;
  /* give  vector a hint on how much memory to allocate */
  array.reserve(size);
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

void seedRandom();

void seedRandom(){
  struct timeval time; 
  gettimeofday(&time, 0);
  long int s = time.tv_usec * getpid(); 
  srand(s);
}

int main(){
  /* initialize random number generator */
  int numItems[] = {10,50,100}; 
  seedRandom();
  for(int i = 0; i < 3; i++){
    int size =  numItems[i];
    /* run 3 different sorts on each of 3 number sets */
    vector<int> almostSorted = makeAlmostSorted(size);
    SortCompare sc1(size,string("almost sorted"),almostSorted);
    sc1.runSorts();
    vector<int> reversed = makeReversed(size);
    SortCompare sc2(size,string("reversed"), reversed);
    sc2.runSorts();
    vector<int> random = makeRandom(size);
    SortCompare sc3(size,string("random"),random);
    sc3.runSorts();
  }

  return 0;
}

