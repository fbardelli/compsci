#include <iostream>
#include <cmath>
#include <vector>
#include <map>
using namespace std;
int main(){
    const int MAX = 50000000;
    vector<int> primes;
    int num = 2;
    primes.push_back(num);
    int prime_fourth_max = (int) pow(MAX-(pow(2,2.0)+pow(2,3.0)), 1.0 / 4);
    int prime_cube_max = (int) pow(MAX-(pow(2,2.0)+pow(2,4.0)), 1.0 / 3);
    int prime_square_max = (int) pow(MAX-(pow(2,3.0)+pow(2,4.0)), 1.0 / 2);
    int primes_below_square_max = 1;
    int primes_below_cube_max = 1;
    int primes_below_fourth_max = 1;
    NUM: while (num < prime_square_max ){
        num++;
        int numsqrt = (int)sqrt(num);
        for(int i = 0; i < primes.size(); i++){
            if (primes[i] > numsqrt){
              break;
            }
            if(num % primes[i] == 0){
                goto NUM;
            }
        }
        if(num > 0)
            primes.push_back(num);
        if(num <= prime_cube_max){
            primes_below_cube_max++;
            if(num <= prime_fourth_max){
                primes_below_fourth_max++;
            }
        }
    }

    primes_below_square_max = primes.size();
/*
    cout << primes_below_square_max << "*" << primes_below_cube_max << "*" << primes_below_fourth_max
         << " = " << primes_below_square_max * primes_below_cube_max * primes_below_fourth_max
         << "\n";
    cout << primes.size() << "\n";

    for (int i = 0; i < primes.size(); i++){
        cout << primes[i] << endl;
    }
*/

    map<uint64_t,bool> seen;
    for(int f=0; f < primes_below_fourth_max; f++){
        for(int c=0; c < primes_below_cube_max; c++){
            for(int s=0; s < primes_below_square_max; s++){
                uint64_t value = (uint64_t)(pow(primes[s],2.0) + pow(primes[c],3.0) + pow(primes[f],4.0));
                if(value < MAX){
                    //cout << primes[s] << "^2 + " << primes[c] << "^3 + " << primes[f] << "^4 = " << value << endl;
                    seen[value] = true;
                }
            }
        }
    }
    cout << seen.size() << endl;
    //cout << prime_fourth_max << " * " << prime_cube_max << " * " << prime_square_max << " = " << prime_fourth_max * prime_cube_max * prime_square_max << endl;
}
