using System;
using System.Collections.Generic;

public class PFact
{
    static public List<long> primeFactors(long numbers) {
        long n = numbers; 
        List<long> factors = new List<long>();
        for (long i = 2; i <= n / i; i++) {
            while (n % i == 0) {
                factors.Add(i);
                n /= i;
            }
        }
        if (n > 1) {
            factors.Add(n);
        }
        return factors;
    }


    static public void Main ()
    {
        long limit             = 600851475143L;
        List<long> factors = primeFactors(limit);
        foreach(long l in factors){
            Console.WriteLine(l);
        }
    }
}
