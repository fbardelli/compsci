using System;
 
public class Fib
{
    static public void Main ()
    {
        int current = 1;
        int next    = 2;
        int sum     = 0;
        while(current < 4000000){
            if(current % 2 == 0){
                sum +=current;
            }
            Console.WriteLine(current);
            int temp = current + next;
            current = next;
            next = temp; 
        }
        Console.WriteLine(sum);

    }
}
