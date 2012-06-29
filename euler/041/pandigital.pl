use strict;
use Data::Dumper;
my @primes = (2);
my $num = 2;
my $primes = @primes;
my %pandigital;
NUM: while($num < 7_654_321){
    print "processing $num\n" if $num % 100_000 == 0;
    #prime if it does not divide evenly into seen primes
    $num++;
    my $sqrt = sqrt($num);
    for my $p (@primes) {
        last if $p > $sqrt;
        next NUM if $num % $p == 0;
    }
    push @primes,$num;
    $primes++;
    my $str = "$num";
    next NUM if (my $count = $str =~ tr/0/0/);
    for my $n (1..(length $str)){
        my $count = eval qq{\$str =~ tr/$n/$n/};
        if($count == 1){
            $pandigital{$num} = 1;
        }else{
            delete $pandigital{$num};
            last;
        }
    }
}
print "done building primes\n";

print ( (reverse sort keys %pandigital)[0] );

