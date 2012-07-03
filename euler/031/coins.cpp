#include <iostream>
using namespace std;
//my @denominations (1, 2, 5, 10, 20, 50, 100, 200);
int main(){
    int combinations = 8; //200*1,100*2,50*4,20*10,10*20,5*40,2*100,1*200
    int total = 0;
    for (int c1 = 0; c1 < 200; c1+=1){
        for ( int c2 = 0; c2 < 200; c2+=2){
            for (int c5 = 0; c5 < 200; c5+=5){
                for ( int c10 = 0; c10 < 200; c10+=10){
                    for ( int c20 = 0; c20 < 200; c20+=20){
                        for (int c50 = 0; c50 < 200; c50+=50){
                            for(int c100 = 0; c100 < 200; c100+=100){
                                if(c1+c2+c5+c10+c20+c50+c100 == 200){
                                    combinations++;
                                }
                                total++;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << combinations << " combinations of " << total << " tries\n";
}
