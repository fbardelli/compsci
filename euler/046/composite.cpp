#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<cmath>
using namespace std;

int main(){
    const int TOP_NUM = 10000;
    int num = 2;
    vector<int> primes;
    map<int, bool>composite_map;
    primes.push_back(num);
    NUM: while (num <= TOP_NUM ){
        num++;
        int numsqrt = (int)sqrt(num);
        for(int i = 0; i < primes.size(); i++){
            if (primes[i] > numsqrt){
              break;
            }
            if(num % primes[i] == 0){
                if(num % 2 != 0){
                    composite_map[num] = false;
                }
                goto NUM;
            }
        }
        primes.push_back(num);
    }
    int sq = 1;
    int last = 0;
    while (last < TOP_NUM){
        last = (sq*sq*2);
        for(int p = 0; p < primes.size(); p++){
            composite_map[(primes[p]+last)] = true;
        }
        sq++;
    }

    map<int, bool>::iterator cmap;
  
    for(cmap = composite_map.begin(); cmap != composite_map.end(); cmap++) {
        if(! cmap->second ){
            cout << cmap->first << " does not have a solution\n";
        }
    }
    return 0;
}
