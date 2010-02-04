// Frank Bardelli
// Advanced C++ Programming (Section WQ6)
// Assignment 1 Part 2 #1
// September 9, 2009
//---------- SOURCE CODE BEGINS HERE ----------

#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
using namespace std;
const int ITERATIONS =  10000;

int main()
{
  // get the time of day
  struct timeval time; 
  gettimeofday(&time, 0);

  // seed the random number generator
  // with $PID and time of day in milliseconds
  long int seed = time.tv_usec * getpid(); 
  srand(seed);

  // initialize counters for evens and odds
  int evens = 0;
  int odds = 0;
  //initialize random number
  long int r = 0;
  for( int i = 0; i < ITERATIONS; i++){
    r = rand();
    //is the random number odd?
    if(r % 2){
      ++odds;
    }
  }
  evens = ITERATIONS - odds;
  //display report
  cout << "With " << ITERATIONS << " Iterations:\n" 
       << "Evens: " << evens << "(" << ( (float)evens / (float)ITERATIONS) * 100.0f << "%)\n"
       << "Odds:  " << odds  << "(" << ( (float)odds / (float)ITERATIONS) * 100.0f  << "%)\n";

}

