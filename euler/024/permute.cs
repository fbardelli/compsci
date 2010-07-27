using System;
using System.Collections.Generic;

/*
A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
*/

public delegate bool PermuteDelegate(List<char> nums);

class Permute
{
    public static bool MyFunc(List<char> nums)
    {
        if(nums.Count==0){
            return false;
        }
        foreach(char n in nums){
           permute(nums);
           Console.WriteLine(n);
        }
        return true;
        //Console.WriteLine("I was called by delegate ...");
    }
    public static void permute(List<char> num) {

        /*my @idx = 0..$#_;
        while ( $code->(@_[@idx]) ) {
            my $p = $#idx;
            --$p while $idx[$p-1] > $idx[$p];
            my $q = $p or return;
            push @idx, reverse splice @idx, $p;
            ++$q while $idx[$p-1] > $idx[$q];
            @idx[$p-1,$q]=@idx[$q,$p-1];
        }*/
    }
    public static void Main()
    {
        List<char> nums = new List<char>{'0','1','2','3','4','5','6','7','8','9'};
        // Instantiation
        PermuteDelegate pDelegate = new PermuteDelegate(MyFunc);

        // Invocation
        pDelegate(nums);
    }
}
