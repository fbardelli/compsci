#include<iostream>
#include<sstream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
enum bouncyType { ASC, DESC, FLAT, BOUNCY };

bouncyType getBouncyType(string st);

int main(){
    long long nonbouncy   = 0;
    const int MAX_POW = 100;
    long long   asc_bounces[10][MAX_POW],
                desc_bounces[10][MAX_POW],
                flat_bounces[10][MAX_POW];
    memset(asc_bounces,0,sizeof(asc_bounces[0])*10);
    memset(desc_bounces,0,sizeof(desc_bounces[0])*10);
    memset(flat_bounces,0,sizeof(flat_bounces[0])*10);
    int i = 1;
    //init first 9
    for(int n = 1; n <= 9; n++){
        flat_bounces[n][i]=1;
        nonbouncy++;
    }
    i++;
    //init first 10-99
    for(char c='1'; c <= '9'; c++){
        for(char d='0'; d <= '9';d++){
            char dig[3] = {c,d,'\0'};
            int bucket = atoi(dig) / 10;
            switch(getBouncyType(string(dig))){
                case ASC:
                    asc_bounces[bucket][i]++;
                    nonbouncy++;
                    break;
                case DESC:
                    desc_bounces[bucket][i]++;
                    nonbouncy++;
                    break;
                case FLAT:
                    flat_bounces[bucket][i]++;
                    nonbouncy++;
                    break;
            }
        }
    }
    i++;

    cout << endl << "below 10e" << i-1 <<" :\t" << nonbouncy << endl;
    while(i <= MAX_POW){
        for(int k = 1; k <= 9; k++){
            desc_bounces[k][i] = asc_bounces[k][i] = 0;
            for(int m = 1; m <= k; m++){
                desc_bounces[k][i] += desc_bounces[m][i-1];
                desc_bounces[k][i] += flat_bounces[m][i-1];
            }
            for(int m = k; m <= 9 ; m++){
                asc_bounces[k][i] += asc_bounces[m][i-1];
                if(m > k){
                    asc_bounces[k][i] += flat_bounces[m][i-1];
                }
            }
            flat_bounces[k][i] = 1; //ex 5555555
            nonbouncy += (flat_bounces[k][i] + asc_bounces[k][i] + desc_bounces[k][i]);
        }
        i++;
        cout << "below 10e" << i-1 <<" :\t" << nonbouncy << endl;
    }
}

bouncyType getBouncyType(string st){
    int len = st.length();
    char last = st[0];
    bouncyType status = FLAT;
    for(int j = 1; j < len; j++){
        if(st[j] > last){
            status = ASC;
            if (status == DESC)
                return BOUNCY; 
        }else if(st[j] < last){
            status = DESC;
            if (status == ASC )
                return BOUNCY;
        }
        last = st[j];
    }
    return status;
}
