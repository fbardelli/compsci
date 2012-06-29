#include <iostream>
using namespace std;

int main()
{
    const int LIMIT  = 1000;
    int maxDecimal   = 0;
    int maxRecurring = 0;

    for(int n = LIMIT - 1; n > 1; n-- )
    {
        int rem = 1;
        int tempRem;
        for(int i = 0; i < n; i++)
        {
            rem = (rem*10)%n;   //Cycle through the remainder up to n places
        }
        tempRem = rem;
        
        int len = 0;
        do
        {
            rem = (rem*10)%n;
            len++;
        } while( rem!=tempRem );
        if(len > maxRecurring)
        {
            maxDecimal   = n;
            maxRecurring = len;
        }
    }
    cout << "1/" << maxDecimal << " has a cycle with " << maxRecurring << " numbers.\n";
    return 0;
}
