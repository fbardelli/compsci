#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<cmath>
using namespace std;

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
    for (int j = 0; j < 10; j++){
      cout << j << ": is " << (prime_map.count(j)? "":"not ")<< "prime\n";
    }
    return 0;
}
