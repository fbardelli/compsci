#include<iostream>
#include<cmath>
#include<cstring>
#include<map>
using namespace std;

int divisor_sum(int i);
int main(){
    int cache[10000];
    memset(cache,0,sizeof(cache[0])*10000);
    for(int i = 1; i < 10000; i++){
        int sum = divisor_sum(i);
        if(sum < 10000){
            cache[i] = sum;
        }
    }
    int amsum = 0;
    for(int i = 1; i < 10000; i++){
        if ( i != cache[i] && i == cache[cache[i]]){
            cout << i << " and " << cache[i] << endl;
            amsum += i;
        }
    }
    cout << "Sum = "<< amsum <<endl;
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
