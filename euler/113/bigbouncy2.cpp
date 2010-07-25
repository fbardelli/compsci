#include<iostream>
#include<sstream>
#include<string>
#include<cstring>
#include<cmath>
#include<map>
#include<vector>
using namespace std;
#define ASC  1
#define DESC 2
#define FLAT 3
#define BOUNCY 4

short isBouncy(int i);

int main(){
    int bouncy = 0;
    long long nonbouncy   = 0;
    long long asc_bounces[10][101];
    long long  desc_bounces[10][101];
    long long  flat_bounces[10][101];
    memset(asc_bounces,0,sizeof(asc_bounces[0])*10);
    memset(desc_bounces,0,sizeof(desc_bounces[0])*10);
    memset(flat_bounces,0,sizeof(flat_bounces[0])*10);
    for(int n = 1; n <= 9; n++){
        flat_bounces[n][0]=1;
        nonbouncy++;
    }
    for(int n = 10; n < 100; n++){
        int bucket = n / 10;
        switch(isBouncy(n)){
            case ASC:
                asc_bounces[bucket][2]++;
                nonbouncy++;
                break;
            case DESC:
                desc_bounces[bucket][2]++;
                nonbouncy++;
                break;
            case FLAT:
                flat_bounces[bucket][2]++;
                nonbouncy++;
                break;
        }
    }
    /*for (int i =0;i<10;i++){
        cout << i << " asc (" << asc_bounces[i][2] << ")"
             << "desc (" << desc_bounces[i][2] << ")"
             << "flat (" << flat_bounces[i][2] <<")\n";
    }*/

    
    int i = 3;
    while(i <= 101){
        cout << endl << "below 10e" << i-1 <<" :\t" << nonbouncy;
        for(int k = 1; k <= 9; k++){
         //   cout << "in " << k <<" Adding 1\n";
            desc_bounces[k][i] = 0; //ex 500000 
            for(int m = 1; m <= k; m++){
           //     cout << "Adding desc " << desc_bounces[m][i-1] << "from digit " << m << " coulumn " << i-1 << endl;
                desc_bounces[k][i] += desc_bounces[m][i-1];
             //   cout << "Adding flat to desc " << flat_bounces[m][i-1] << "from digit " << m << " coulumn " << i-1 << endl;
                desc_bounces[k][i] += flat_bounces[m][i-1];
            }
            asc_bounces[k][i] = 0;
            for(int m = k; m <= 9 ; m++){
               // cout << "Adding asc " << desc_bounces[m][i-1] << "from digit " << m << " coulumn " << i-1 << endl;
                asc_bounces[k][i] += asc_bounces[m][i-1];
                if(m > k){
                 //   cout << "Adding flat to asc" << flat_bounces[m][i-1] << "from digit " << m << " coulumn " << i-1 << endl;
                    asc_bounces[k][i] += flat_bounces[m][i-1];
                }
            }
            //cout << "Adding 1 to flat for digit " << k << " column " << i << endl;
            flat_bounces[k][i] = 1; //ex 5555555
            /*cout << i << " asc (" << asc_bounces[k][i] << ")"
                 << "desc (" << desc_bounces[k][i] << ")"
                 << "flat (" << flat_bounces[k][i] <<")\n";*/
            nonbouncy += desc_bounces[k][i];
            nonbouncy += flat_bounces[k][i];
            nonbouncy += asc_bounces[k][i];
        }
        i++;
    }
    cout << endl << "below 10e" << i-1 <<" :\t" << nonbouncy << endl;
}

short isBouncy(int i){
    stringstream s;
    s << i;
    string st = s.str();
    int increasing = 0;
    int decreasing = 0;
    int len = st.length();
    char last = st[0];
    for(int j = 1; j < len; j++){
        if(st[j] > last){
            increasing++;
            if (decreasing > 0)
                return BOUNCY; 
        }else if(st[j] < last){
            decreasing++;
            if (increasing > 0)
                return BOUNCY;
        }
        last = st[j];
    }
    if (increasing>0){
        return ASC;
    }else if(decreasing > 0){
        return DESC;
    }else{
        return FLAT;
    }
}
