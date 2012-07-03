#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<cmath>
using namespace std;

int main(){
    const int TOP_NUM = 150000;
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
    int start_idx, end_idx, top_sum;
    int max_consecutive = 0;
    vector<int> consecutive_distinct;
    const int DISTINCT_FACTORS = 4;
    NEXTNUM: for (int i = 1; i <= 150000 ; i++){
        int factors = 0;
        for (int j = 0; primes[j] < i; j++){
            if(i % primes[j] == 0){
                factors++;
            }
        }
        if(factors == DISTINCT_FACTORS){
            consecutive_distinct.push_back(i);
        } else {
            consecutive_distinct.clear();
        }
        if(consecutive_distinct.size() == DISTINCT_FACTORS){
            for(int k = 0; k < DISTINCT_FACTORS; k++){
                cout << consecutive_distinct[k] << endl;
            }
            break;
        }

    }

    return 0;
}
