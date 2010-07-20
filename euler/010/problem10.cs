using System;
using System.Collections.Generic;

public class PFact
{
    static public void Main ()
    {
        const long TOP_NUM = 2000000;
        long num = 2;
        List <long> primes = new List<long>();
        primes.Add(num);
        long sum = primes[0];
        NUM: while ( num < TOP_NUM ){
            num++;
            double numsqrt = Math.Sqrt(num);
            foreach ( long p in primes) {
                if( p > numsqrt){
                    break;
                }
                if(num % p == 0){
                    goto NUM;
                }
            }
            primes.Add(num);
            sum += num;
        }
        Console.WriteLine(sum);

    }
}
