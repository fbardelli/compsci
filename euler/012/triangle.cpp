#include<iostream>
#include<cmath>
using namespace std;

int main(){
    //divisors
    const int DIVISORS = 500;
    long trisum = 0;
    long i = 0;
    while(1){
        i++;
        trisum += i;
        long sumsqrt = (long) sqrt(trisum);
        int divisors = 2;
        cout << trisum << " is divisible by: " << trisum << ", 1, ";
        for(int j = 2; j <= sumsqrt; j++){
            if( trisum % j == 0){
                divisors++;
                cout << j << ", ";
                if( j != trisum/j){
                    divisors++;
                    cout << trisum/j << ", ";
                }
            }
        }
        cout << endl << trisum << " has " << divisors << " divisors\n"; 
        if (divisors > 500){
            break;
        }
        cout <<endl;
    }
}
