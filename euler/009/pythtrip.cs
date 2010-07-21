using System;
/*
 Pythagorean triplet is a set of three natural numbers, a  < b  < c, for which,
 a^(2) + b^(2) = c^(2)

 For example, 3^(2) + 4^(2) = 9 + 16 = 25 = 5^(2).

 There exists exactly one Pythagorean triplet for which a + b + c = 1000.
 Find the product abc.
*/

public class Pyth
{
    static public void Main ()
    {
        int target = 1000;
        /* 
           Assumptions:
           sum of squares < square of sums
           (a)^2 + (b)^2 < (a+b)^2
           1^2 + 2^2 < (1+2)^2
           so c < a + b
           so a < b < c < (a + b)
           if ((a+b)+c) = 1000 then (a+b)>500 and c < 500
           min c is 334 since a < b < c and a+b+c=1000 
           332+333+334=999 < 1000
        */
        int max_c  = (target/2) - 1;
        int min_c  = (target/3) + 1;
        Console.WriteLine(max_c);
        int max_b = max_c - 1;
        int min_b = min_c - 1;
        int[] squares_table = new int[max_c+1];
        for(int i = 0; i <= max_c; i++){
           squares_table[i] = (int)Math.Pow(i,2);
        }
        for(int c = min_c;c <= max_c; c++){
            for(int b = min_b;b <= max_b;b++){
                int a = 1000 - b - c;
                if( (squares_table[a]+squares_table[b])==squares_table[c]){
                   Console.WriteLine( "a: " + a + " b: " + b + " c: " + c ); 
                   Console.WriteLine( squares_table[a] + " + " + squares_table[b] + " = " + squares_table[c] ); 
                   int product = a*b*c;
                   Console.WriteLine("a*b*c = " + product);
                }
            }
        }
    }
}
 
