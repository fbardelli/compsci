#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
#include<vector>
using namespace std;

bool isBouncy(long long i);
int main(){
    int bouncy = 0;
    double proportion = 0.0;
    int last_log_10 = 0;
    vector<long long> nonbouncy;
    for(long long n = 0; n < 100; n++){
        nonbouncy.push_back(n);
    }
    int i = 2;
    while(i <= 10){
        long long factor_10 = pow(10.0,(double)i);
        cout<<factor_10;
        int current_size = nonbouncy.size();
        for(int k = 1; k <= 9; k++){
            for(int j = 0; j < current_size;  j++){
                //cout << "kf10" << (k*factor_10);
                long long value = (k*factor_10)+ nonbouncy[j];
                //cout << "checking "<< value << endl;
                if(!isBouncy(value)){
                    nonbouncy.push_back(value);
                }
            }
        }
        i++;
    }
    cout << endl << nonbouncy.size() - 1L;
}

bool isBouncy(long long i){
    stringstream s;
    string st;
    s << i;
    st = s.str();
    int increasing = 0;
    int decreasing = 0;
    int len = st.length();
    char last = st[0];
    for(int j = 1; j < len; j++){
        if(st[j] > last){
            increasing++;
            if (decreasing > 0)
                return true; 
        }else if(st[j] < last){
            decreasing++;
            if (increasing > 0)
                return true;
        }
        last = st[j];
    }
    return false;
}
