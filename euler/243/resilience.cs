using System;
using System.Collections.Generic;
using Mehroz;

public class Resilience
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
        Fraction target = new Fraction(4,10);
        //Fraction target = new Fraction(15499,94744);
        for(int denom = 2; denom <= 12; denom++){
            int resilience = 0;
            for( int i = 1; i < denom; i++){
                Fraction f = new Fraction(i,denom);
                //Console.WriteLine(f);
                if(f.Denominator  == denom){
                    resilience++;
                }
            }
            Fraction r = new Fraction(resilience,denom-1);
            Console.WriteLine("{0}: {1}",denom,r);
            if(r < target){
//                Console.WriteLine(denom);
            }
        }
    }
}
