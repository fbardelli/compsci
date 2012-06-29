#include<iostream>
#include<cmath>
using namespace std;

/*Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

5x5 = 25

2,2     3,2     3,3     2,3     1,3     1,2     1,1     2,1     3,1
4,1     4,2     4,3     4,4     3,4     2,4     1,4     0,4     0,3     0,2     0,1     0,0     1,0     2,0     3,0     4,0
It can be verified that the sum of the numbers on the diagonals is 101.

(at center)
right 1
down 1 (at a digonal)
left 2 (at a diagonal)
up 2   (at a diagonal)
right 2 (at a diagonal) 
right 1 
down 3  (at a diagonal)
left 4  (at a diagonal)
up 4    (at a diagonal)
right 4 (at a diagonal)
right 1
down 5  (at a diagonal)
left 6  (at a diagonal)
up 6    (at a diagonal)
right 6 (at a diagonal)
right 1
What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
*/

int main(){
    //const int MAX_SIZE = 1001;
    //const unsigned long long MAX_SIZE = 1001;
    const unsigned long long MAX_SIZE = 100000001;
    unsigned long long sum = 1;
    unsigned long long counter = 1;
    for(unsigned long long i = 2; i < MAX_SIZE; i += 2){
        for(int j = 0; j < 4; j++){
            counter += i;
            sum += counter;
        }
    }
    cout << sum << endl;
}

