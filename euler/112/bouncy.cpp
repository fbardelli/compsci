#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
using namespace std;

int main(){
    int i = 0;
    int bouncy = 0;
    double proportion = 0.0;
    while(proportion <= 0.99){
        i++;
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
            }else if(st[j] < last){
                decreasing++;
            }
            last = st[j];
        }
        if(increasing > 0 && decreasing > 0){
            //cout << i << " is BoUnCy\n";
            bouncy++;
        }
        proportion = (double)bouncy/(double)i;
    }
    i--;
    cout << "bouncy " << bouncy << " out of " << i << endl;
    cout << "Bouncy proportion is " << proportion;
}
