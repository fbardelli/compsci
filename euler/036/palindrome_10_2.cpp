#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
using namespace std;

bool is_palindrome(int num);
bool is_palindrome(string s);
string itoa(int value, int base);

int main(){
    int sum = 0;
    for(int i=1; i < 1000000; i++){
       string binn = itoa(i,2);
       if( is_palindrome(i) && is_palindrome(binn)){
         cout << i << ":" << binn << endl;
         sum += i;
       }
    }
    cout << "sum: " << sum << endl;
    return 0;
}

bool is_palindrome(string s){
    int length = s.length();
    //cout << s << " L:" << length <<endl;
    int mid = length / 2;
    length--;
    for(int i = 0; i < mid; i++){
        if(s[i] != s[length-i]){
            return false;
        }
    }
    //cout << s << " is pal" <<endl;
    return true;
}

bool is_palindrome(int num){
    int digits = log10(num) + 1;
    stringstream ss;
    ss << num;
    string s = ss.str();
    return is_palindrome(s);
}

string itoa(int value, int base) {
    enum { kMaxDigits = 35 };
    std::string buf;
    buf.reserve( kMaxDigits ); // Pre-allocate enough space.
    
    // check that the base if valid
    if (base < 2 || base > 16) return buf;
    int quotient = value;
    
    // Translating number to string with base:
    do {
        buf += "0123456789abcdef"[ std::abs( quotient % base ) ];
        quotient /= base;
    } while ( quotient );
    
    // Append the negative sign for base 10
    if ( value < 0 && base == 10) buf += '-';
    
    std::reverse( buf.begin(), buf.end() );
    return buf;
}

