#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;

void displaynums(int nums[],int num_args, int arg_index, list<int> num_stack);

int main(int argc, char *argv[]){
  int * nums;
  int num_args = argc - 1;
  list<int> num_stack;
  if(num_args < 1){
    cout << "this command requires a list of numbers\n";
    exit(1);
  }
  nums = new int [num_args];
  for(int i=0;i<num_args;i++){
    nums[i] = atoi(argv[i+1]);
    if (nums[i] <= 0){
      cout << "arguments must be numeric and greater than 0\n";
      exit(1);
    }
  }
  displaynums(nums,num_args,0,num_stack);
  delete [] nums;
  return 0;
}

void displaynums(int nums[],int num_args, int arg_index, list<int> num_stack){
  int next = arg_index + 1;
  for (int i =0;i < nums[arg_index];i++){
    if (next == num_args){
      list<int>::const_iterator it;
      cout << "[";
      for(it=num_stack.begin(); it!=num_stack.end(); it++){
        cout << *it << ",";
      }
      cout << i << "]\n";
    }else{
      num_stack.push_back(i);
      displaynums(nums,num_args,next,num_stack);
      num_stack.pop_back();
    }
  }
}
