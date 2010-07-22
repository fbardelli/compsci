#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<cmath>
using namespace std;
struct highest_prime {
    int primeval;
    int start_idx;
    int end_idx;
};

int main(){
    const int TOP_NUM = 1000000;
    int num = 2;
    vector<int> primes;
    map<int, bool>prime_map;
    primes.push_back(num);
    prime_map[num]=true;
    NUM: while (num < TOP_NUM ){
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
        primes.push_back(num);
        prime_map[num]=true;
    }
    int total_primes = primes.size();
    int max_range = 0;
    int small_sum = 0;
    for (int j = 0; j < total_primes ; j++){
        small_sum += primes[j];
        if(small_sum < TOP_NUM){
            max_range++;
        }else{
            break;
        }
    }
    int start_prime, end_prime;
    int max_sum     = 0;
    NEXTNUM: for (int i = 0; i < total_primes ; i++){
        start_prime = i;
        int sum = primes[i];
        for(int j = 1; j < max_range; j++){
            sum += primes[i+j];
            if(sum > TOP_NUM){
                goto NEXTNUM;
            }
            if(prime_map[sum]){
                cout << sum << "is the prime result of " << i << "through" << j << endl;
            }
        }
    }
    cout << max_range << ":"<< small_sum;
   //   cout << j << ": is " << (prime_map.count(j)? "":"not ")<< "prime\n";
    return 0;
}
