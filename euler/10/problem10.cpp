#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main ()
{
    const long TOP_NUM = 2000000;
    long num = 2;
    vector <long> primes;
    primes.push_back(num);
    long sum = primes[0];
    NUM: while ( num < TOP_NUM ){
        num++;
        double numsqrt = sqrt(num);
        for (vector<long>::iterator it = primes.begin(); it!=primes.end(); ++it) {
            if( *it > numsqrt){
                break;
            }
            if(num % *it == 0){
                goto NUM;
            }
        }
        primes.push_back(num);
        sum += num;
    }
    cout << sum << endl;
    return 0;
}
