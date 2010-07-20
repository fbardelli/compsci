#include <iostream>
using namespace std;
/*
n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
*/
int main (){
  int cache[1000000];
  int max = 0;
  int maxidx = 0;
  for (int i = 0; i < 1000000; i++){
      cache[i] = -1;
  }
  for (int i = 1; i < 1000000 ; i++){
  //for (long long i = 113383; i < 113384; i++){
      int size = 1;
      long long seq = i;
      //cout << "\nProcessing " << i << endl;
      while ( seq != 1 ){
          //cout << seq << " -> ";
          if(seq < 1000000 ){
              if (cache[seq] != -1){
                size += cache[seq];
                break;
              }
          } 
          size++;
          if ( seq % 2 ){
              seq = ((seq * 3) + 1);
          } else {
              seq = seq/2;
          }
      }
      //cout << "1\n";
      cache[i] = size;
      if(size > max){
        max = size;
        maxidx = i;
      }
  }
  cout << maxidx << ":" << max;
}
