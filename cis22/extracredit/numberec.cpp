#include <iostream>
#include <stdlib.h>
using namespace std;

void displayArray(int * nums, int index, int * num_stack, int size);

int main(int argc, char *argv[]){
  int num_args = argc;
  int size = num_args - 1;
  int *nums, *num_stack;
  /* validate that numbers were entered*/
  if(num_args < 2){
    cout << "this command requires a list of numbers\n";
    exit(1);
  }
  nums = new int(size);
  num_stack = new int(size);
  /* validate that numbers are valid */
  for(int i = 0; i < size; i++){
    nums[i] = atoi(argv[i+1]);
    if (nums[i] <= 0){
      cout << "arguments must be numeric and greater than 0\n";
      exit(1);
    }
  }
  displayArray(nums, 0, num_stack, size);
  delete[] nums;
  delete[] num_stack;
  return 0;
}

void displayArray(int * nums, int index, int * num_stack, int size){
  int next_index = index + 1;
  for ( int i = 0; i < nums[index]; i++ ){
    /* store the value at current index so we can display it later */
    num_stack[index] = i;
    /* if we are at the last digit output the contents of the stack*/
    if (next_index == size){
      cout << "[";
      for(int j = 0; j < size-1; j++){
        cout << num_stack[j] << ",";
      }
      cout << i << "]\n";
    }else{
      displayArray(nums, next_index, num_stack, size);
    }
  }
}
