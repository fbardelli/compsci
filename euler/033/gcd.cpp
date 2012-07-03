#include <iostream>
#include <sstream>
using namespace std;

int main(){
    int numProduct = 8;
    int denomProduct = 800;
    int gcd;
    ostringstream strm;
    int numProductCopy = numProduct;
    int denomProductCopy = denomProduct;
    strm << "GCD " << numProduct << " / " << denomProduct;
    while(numProduct > 0){
        int tmp = numProduct;
        numProduct = denomProduct % numProduct;
        denomProduct = tmp;
        gcd = denomProduct;
        cout << " PROCESSING " << numProduct << " / " << denomProduct << endl;
    }

    cout << strm.str() << " = " << gcd << endl;
    cout << "Reduced " << numProductCopy/gcd << " / " << denomProductCopy/gcd << endl;
    return 0;
}

