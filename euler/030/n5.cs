using System;

public class nFive {
    public static void Main(){
        int[] nthpowers5 = new int[10];
        for(int i=0;i <=9; i++){
            nthpowers5[i] = (int)Math.Pow(i,5.0);
            Console.WriteLine(nthpowers5[i]);
        }
        int max_digits = 0;
        int largest = 0;
        int big_sum = 0;
        while(true){
            max_digits++;
            int digit = nthpowers5[9]*max_digits;
            if(max_digits > Math.Log10(digit)){
                break;
            }
            largest = digit;
        }
        Console.WriteLine("max digits " + max_digits + " largest " + largest);
        for(int i = 2; i < largest; i ++){
            int x = i;
            int sum = 0;
            while(x >= 1){
                int y = x % 10;
                x = x / 10;
                sum += nthpowers5[y];
            }
            if (i == sum){
                Console.WriteLine(i + " Works!");
                big_sum+=i;
            }
        }
        Console.WriteLine("Total: "+big_sum);
    }

}

