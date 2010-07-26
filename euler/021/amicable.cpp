#include<iostream>
#include<cmath>
#include<map>
using namespace std;

int divisor_sum(int i);
int main(){
    map<int,int> cache;
    for(int i = 1; i < 10000; i++){
        int sum = divisor_sum(i);
        cache[i] = sum;
//        cout << i << " = " << sum << endl;
    }
    for(int i = 1; i < 10000; i++){
        if ( i == cache[cache[i]]){
            cout << i << " and " << cache[i] << endl;
        }
    }
    return 0;
}

int divisor_sum(int i){
    int sumsqrt = (int) sqrt(i);
    int div_sum = 1;
    for(int j = 2; j <= sumsqrt; j++){
        if( i % j == 0){
            div_sum += j; 
            if( j != i/j){
                div_sum += (i/j);
            }
        }
    }
    return div_sum;
}
