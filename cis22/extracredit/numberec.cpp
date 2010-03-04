
#include <iostream>
#include <stdlib.h>
using namespace std;

void displaynums(int nums[],int num_args);

int main(int argc, char *argv[]){
  int num_args = argc - 1;
  if(num_args < 1){
    cout << "this command requires a list of numbers\n";
    exit(1);
  }
  int * nums;
  nums = new int [num_args];
  for(int i=0;i<num_args;i++){
    nums[i] = atoi(argv[i+1]);
  }
  for(int j = 0; j<num_args; j++){
    cout << nums[j] << endl;
  } 
  delete [] nums;
  return 0;
}

void displaynums(int nums[],int num_args){


}
