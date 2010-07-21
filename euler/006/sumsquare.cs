using System;

public class SumSq
{
    static public void Main ()
    {
        long sumsquare = 0, squaresum = 0;

        for(int i = 1; i <=100; i++){
            squaresum += i;
            sumsquare += (long) Math.Pow(i,2);
        }
        long sumdiff = (long)Math.Pow(squaresum,2) - sumsquare;
        Console.WriteLine(sumdiff);
    }
}

