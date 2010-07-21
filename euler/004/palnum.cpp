#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

bool is_palindrome(int num);

int main()
{
    int MAX = 999;
    int LOW = 900;
    int max_pal = 0;
    int max_i   = 0;
    int max_j   = 0;
    for(int i = MAX; i > LOW; i--){
        for(int j = MAX; j > LOW; j--){
           int product = i * j;
           //cout << i << "*" << j << " = " << product;
           if( is_palindrome(product) ){
               cout << "found pal " << product << endl;
               if( product > max_pal) {
                   max_pal = product;
                   max_i   = i;
                   max_j   = j;
               }
           }

        }
    }
    cout << "max_pal is " << max_pal << " the product of " << max_i << " * " << max_j << endl;
}

bool is_palindrome(int num){
    int digits = log10(num) + 1;
    int mid = digits / 2;
    digits--;
    stringstream ss;
    ss << num;
    string s = ss.str();
    //cout << "checking string " << s << endl;
    for(int i = 0; i < mid; i++){
        //cout << s[i] << ":"  << s[digits-i] << endl;
        if(s[i] != s[digits-i]){
            return false;
        }
    }
    return true;
}
