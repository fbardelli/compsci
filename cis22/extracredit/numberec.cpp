#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

void displaynums(vector<int> nums, int arg_index, vector<int> num_stack);

int main(int argc, char *argv[]){
  int num_args = argc;
  /* using vectors because they are easier to manage than dynamic arrays, 
     have a size() method and can be manipulted like stacks*/
  vector<int> nums, num_stack;
  /* validate that numbers were entered*/
  if(num_args < 1){
    cout << "this command requires a vector of numbers\n";
    exit(1);
  }
  /* validate that numbers are valid */
  for(int i = 1; i < num_args; i++){
    nums.push_back(atoi(argv[i]));
    if (nums[i-1] <= 0){
      cout << "arguments must be numeric and greater than 0\n";
      exit(1);
    }
  }
  displaynums(nums, 0, num_stack);
  return 0;
}

void displaynums(vector<int> nums, int index, vector<int> num_stack){
  int next = index + 1;
  for ( int i = 0; i < nums[index]; i++ ){
    if (next == nums.size()){
      cout << "[";
      for(int j = 0; j < num_stack.size(); j++){
        cout << num_stack[j] << ",";
      }
      cout << i << "]\n";
    }else{
      num_stack.push_back(i);
      displaynums(nums, next, num_stack);
      num_stack.pop_back();
    }
  }
}
