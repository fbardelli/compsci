#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<cmath>
using namespace std;

void findNumSums(int, vector<int>, int, int&, int&);

int main(){
    const int TOP_NUM = 150000;
    int num = 2;
    vector<int> primes;
    map<int, bool>prime_map;
    primes.push_back(num);
    prime_map[num]=true;
    NUM: while (num < TOP_NUM ){
        num++;
        int numsqrt = (int)sqrt(num);
        for(int i = 0; i < primes.size(); i++){
            if (primes[i] > numsqrt){
              break;
            }
            if(num % primes[i] == 0){
                goto NUM;
            }
        }
        primes.push_back(num);
        prime_map[num]=true;
    }
	for(int i = 0; i < primes.size(); i++){
//		cout << primes[i] << "\n";
	}
	for(int n = 3; n <= 10; n++){
		int j = 0;
		while( primes[j] < n){
			j++;
		}
		cout << "n: " << n << " j: " << j << " p: " << primes[j-1] << endl;
		int count = 0;
		int runningSum = 0;
		findNumSums(n,primes,j-1,count,runningSum);
		cout << "count:" << count << "\n";
	}
}

void findNumSums(int number, vector<int> primes, int highestPrimeIndex, int &count, int &runningSum){
	if( highestPrimeIndex < 0)
		return;
	cout << "running Sum "<< runningSum << "\n";
	int currentPrimeIndex = highestPrimeIndex;
	while(primes[currentPrimeIndex] + runningSum <= number){
		runningSum += primes[currentPrimeIndex];
		cout << "running Sum +" << primes[currentPrimeIndex] << " = "<< runningSum << "\n";
		if(runningSum == number){
			count++;
			if(currentPrimeIndex > 0){
				currentPrimeIndex--;
				findNumSums(number,primes,currentPrimeIndex,count,runningSum);
			}
		}
	}
	if( highestPrimeIndex > 0 ){
		highestPrimeIndex--;
		cout << "changing highest index to " << primes[highestPrimeIndex] << " for " << number << "\n";
		findNumSums(number,primes,highestPrimeIndex,count,runningSum);
	}
}


void findPrimeSums( int targetNumber, vector<int> stack, vector<int> primes, int highestIndex, int &count ){
	if(highestPrimeIndex < 0)
		return;
	
// stack [], highestIndex, count
//7 too low
//7+7 too high, next
//7+5 too high, next
//7+3 Great! next [1]
//7+2 too low, add more
//7+2+2 too high next
//none left, decrement top
//5 too low
//5+5 Great, next [2]
//5+3 too low
//5+3+3 too high
//5+3+2 Great [3]
//5+2 too low
//5+2+2 too low
//5+2+2+2 too high,next
//3 too low
//3+3 too low
//3+3+3 too low
//3+3+3+3 too high
//3+3+3+2 too high
//3+3+2 too low
//3+3+2+2 great [4]
//3+2 too low
//3+2+2 too low
//3+2+2+2 too low
//3+2+2+2+2 too high, next
//2 too low
//2+2 too low
//2+2+2 too low
//2+2+2+2 too low
//2+2+2+2+2 Great [5]

}
