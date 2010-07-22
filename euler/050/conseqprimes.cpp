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
    int start_idx, end_idx, top_sum;
    int max_consecutive = 0;
    NEXTNUM: for (int i = 0; i < total_primes ; i++){
        int sum = primes[i];
        int j = 0;
        while(sum < TOP_NUM && (i+j)< total_primes ) {
            j++;
            if(prime_map[sum]){
                //cout << sum << "is the prime result of " << i << "through" << i+j << endl;
                if(j>max_consecutive){
                    max_consecutive = j;
                    start_idx = i;
                    end_idx = i+j;
                    top_sum = sum;
                }
            }
            sum += primes[i+j];
        }
    }
    cout << top_sum << " is the prime result of " << end_idx-start_idx << " terms " << endl;
    int s = 0;
    for (int i=start_idx; i < end_idx; i++){
       s += primes[i];
       cout << primes[i] << " + ";
    }
    cout << " = " << s << endl;
    return 0;
}
