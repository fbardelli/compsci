#include <iostream>
#include <cmath>
#include <sstream>
#include <cstdlib>
using namespace std;


int main(){
    long double num = pow(2.0,1000);
    int decimal_places = log10(num);
    stringstream ss;
    ss.precision(0);
    ss << fixed  << num;
    string bignumstr = ss.str();
    int sum = 0;
    for(int i = 0; i < bignumstr.size(); i++){
        cout << i << ":" << bignumstr.at(i) << endl;
        sum += atoi((bignumstr.substr(i,1)).c_str());
    }
    cout << sum << endl;
    return 0;
}
