#include <iostream>
#include <map>
#include <vector>
using namespace std;
int fact[10];
int factorial(int);
int countChain(int, map<int,bool> &seen,map <int,int> &cache);
int main(){
    //int fact[10];
    int sixtyTerms = 0;
    for(int i = 0; i < 10; i++){
        //cout << "factorial(" << i << ") = " << factorial(i) << endl;
        fact[i] = factorial(i);
    }
    map<int,int> cache;
    for (int i = 1; i < 1000000; i++){
        map<int,bool> seen;
        //cout << i;
        seen[i] = true;
        int size = countChain(i,seen,cache);
        cache[i] = size;
        if ( size == 60){
            //cout << i << " = (" << size << ")\n";
            sixtyTerms++;
        }
    }
    cout << sixtyTerms << " numbers have 60 terms " << endl;

}

int factorial(int num){
    int fac = 1;
    for(int i = num; i > 0; i--){
        fac*=i;
    }
    return fac;
}

int countChain(int i, map<int,bool> &seen,map <int,int> &cache){
    int n = i;
    int sum = 0;
    while(n > 0){
        sum += fact[n%10];
        n /= 10;
    }
    if ( cache.find(sum) != cache.end()) {
        return seen.size() + cache[sum];
    }
    if ( seen.find(sum) == seen.end()){
        seen[sum] = true;
        return countChain(sum,seen,cache);
    }else{
        return seen.size();
    }
}
