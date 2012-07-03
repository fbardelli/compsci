#include <iostream>
using namespace std;

int main(){
    int numProduct = 1;
    int denomProduct = 1;
    for(int num = 10; num < 100; num++){
        for(int denom = 10; denom < 100; denom++){
            if ( !(num % 11 == 0 && denom % 11 == 0) ){
                int tens = num / 10;
                int nCancelled = num % 10;
                int ones = denom % 10;
                int dCancelled = denom / 10;
                if( ((double)num/(double)denom) ==((double)tens/(double)ones)){
                    if (nCancelled == dCancelled){
                        cout << num << "/" << denom << " == " << tens << "/" << ones << endl;
                        numProduct *= tens;
                        denomProduct *= ones;
                    }
                }
            }
        }
    }
    int gcd;
    int numProductCopy = numProduct;
    int denomProductCopy = denomProduct;
    while(numProduct > 0){
        int tmp = numProduct;
        numProduct = denomProduct % numProduct;
        denomProduct = tmp;
        gcd = denomProduct;
    }
    cout << "PRODUCT: " << numProductCopy/gcd << " / " << denomProductCopy/gcd << endl;
    return 0;
}
