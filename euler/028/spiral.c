#include <stdio.h>

int main(){
    //const int MAX_SIZE = 1001;
    //const unsigned long long MAX_SIZE = 1001;
    const unsigned long long MAX_SIZE = 100000001;
    unsigned long long sum = 1;
    unsigned long long counter = 1;
    unsigned long long i;
    int j;
    for(i= 2; i < MAX_SIZE; i += 2){
        for(j = 0; j < 4; j++){
            counter += i;
            sum += counter;
        }
    }
    printf("%llu\n",sum);
    return 0;
}

