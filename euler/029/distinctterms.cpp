#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<cmath>
using namespace std;

int main(){
 
    map<double, bool>distinct_map;
    for(int base = 2; base <= 100; base++){
        for(int exp = 2; exp <= 100; exp++){
            distinct_map[ (double)pow((double)base,(double)exp) ] = true;
        }
    }
    cout << distinct_map.size() << endl;
    return 0;
}
