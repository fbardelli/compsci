
#include <iostream>
#include <stdlib.h>
using namespace std;

void displaynums(int nums[],int num_args, int arg_index, char * append);

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
  displaynums(nums,num_args,0,"[");
  delete [] nums;
  return 0;
}

void displaynums(int nums[],int num_args, int arg_index,char append[]){
  if (arg_index == num_args - 1){
      for(int i=0; i < nums[arg_index-1]; i++){
        cout << append << i << " ]" << endl;
      }
  }else{
    for(int j = 0; j < nums[arg_index]; j++){
      char *str;
      sprintf(str,"%s %d, ",append,j);
      displaynums(nums,num_args,arg_index+1,str);
    }
  }
 
}
