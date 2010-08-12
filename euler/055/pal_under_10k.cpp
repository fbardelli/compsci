#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

bool is_palindrome(unsigned long long num);

unsigned long long reverse_num (unsigned long long num);

int main()
{
    unsigned long long MAX = 10000;
    int total = 0;
    for(unsigned long long i = 1; i < MAX; i++){
       unsigned long long sum = i + reverse_num(i);
       unsigned long long tries = 1;
       //cout << i << " + " << reverse_num(i) << " = " << sum << endl;
       while( ! is_palindrome(sum) ){
           //cout << "\t" << sum << " + " << reverse_num(sum) << " = ";
           sum = (sum + reverse_num(sum));
           //cout << sum << endl;
           if(tries++ > 50){
               //cout << i << " is a Lychrel number\n"; 
               total++;
               break;
           }
       }
    }
    cout << "There are " << total << " Lychrel numbers under " << MAX <<"\n"; 
    return 0;
}

unsigned long long reverse_num (unsigned long long num){
    stringstream ss;
    ss << num;
    string s = ss.str();
    reverse(s.begin(),s.end());
    return atol(s.c_str());
}

bool is_palindrome(unsigned long long num){
    unsigned long long digits = log10(num) + 1;
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
