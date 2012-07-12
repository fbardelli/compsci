#include <iostream>
#include <sstream>
using namespace std;

int gcd( int numerator, int denominator);

int main(){
    int currGCD;
    ostringstream strm;
    double target = 15499.0/94744.0;
    double lowest = 1;
    double last = 2;
    cout << "target:" << target << endl;
    //double target = 4.0/10.0;
    unsigned long long denom =2;
    unsigned long long step = 1;
    while( lowest > target ){
        int resilience = 0;
        for( int i = 1; i < denom; i++){
            int currGCD = gcd(i,denom);
            if(currGCD == 1){
                resilience++;
            }
        }
        double r = (double)resilience/((double)denom-1);
        if( r < lowest ){
            cout << "new low: " << denom << ":" << resilience << "/" << denom-1 <<endl;
            cout << "diff from last: " << denom - last << " target: "<< target << " r: " << r << endl;
            step = denom - last;
            last = denom;
            lowest = r;
        }
        if( r < target){
            cout << "lowest!\n";
            cout << denom << ":" << resilience << "/" << denom-1 <<endl;
            exit(0);
        }
        denom += step;
    }
    return 0;
}

int gcd( int numerator, int denominator){
    int _gcd = 0;
    while(numerator > 0){
        int tmp = numerator;
        numerator = denominator % numerator;
        denominator = tmp;
        _gcd = denominator;
    }
    return _gcd;
}
