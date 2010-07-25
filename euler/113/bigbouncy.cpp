#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
#include<vector>
using namespace std;

bool isBouncy(string st);
int main(){
    int bouncy = 0;
    int last_log_10 = 0;
    vector<string> nonbouncy;
    for(int n = 0; n < 100; n++){
        stringstream s;
        s << n;
        string st = s.str();
        nonbouncy.push_back(st);
    }
    int i = 2;
    while(i < 100){
        cout << endl << "below 10e" << i <<" :" << nonbouncy.size() << endl;
        int current_size = nonbouncy.size();
        for(char k = '1'; k <= '9'; k++){
            for(int j = 0; j < current_size;  j++){
                string value = string(1,k);
                string nb = nonbouncy[j];
                int lendiff = i - nb.length();
                if(lendiff >0){
                    value.append(string(lendiff,'0'));
                }
                value.append(nb);
                //cout << "checking " << value <<"\n";
                if(!isBouncy(value)){
                    //cout << "checking " << value <<"\n";
                    nonbouncy.push_back(value);
                }
            }
        }
        i++;
    }
    cout << endl << nonbouncy.size() << endl;
}

bool isBouncy(string st){
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
