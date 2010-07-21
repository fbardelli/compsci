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
        int max_c  = target;
        Console.WriteLine(max_c);
        int max_b = max_c - 1;
        int max_a = max_b - 1;
        int[] squares_table = new int[max_c];
        for(int i = 0; i < max_c; i++){
           squares_table[i] = (int)Math.Pow(i+1,2);
           Console.WriteLine(squares_table[i]);
        }
    }
}
 
