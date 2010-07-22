import java.util.ArrayList;
import java.util.List;

public class PrimeFactors {
    public static List<Long> primeFactors(long numbers) {
        long n = numbers; 
        List<Long> factors = new ArrayList<Long>();
        for (long i = 2; i <= n / i; i++) {
            while (n % i == 0) {
                factors.add(i);
                n /= i;
            }
        }
        if (n > 1) {
            factors.add(n);
        }
        return factors;
    }

    public static void main(String[] args) {
        for (Long integer : primeFactors(600851475143L)) {
            System.out.println(integer);
        }
    }
}

