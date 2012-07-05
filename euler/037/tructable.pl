use lib '../lib/perl/';
use Euler::Primes;
use strict;

my $prime_list = Euler::Primes::get_prime_map({maximum => 999999, as_list=>1});
my $prime_map  = { map { $_=>1 } @$prime_list}; 

my $sum = 0;
PRIME: for my $prime ( @$prime_list ) {
    next if $prime < 10;
    my $number = "$prime";
    my @primes;
    for(1..(length($number)-1)){
        push(@primes,substr($number, 0, $_));
        next PRIME unless exists $prime_map->{(substr($number, 0, $_))};
        push(@primes,substr($number, -$_));
        next PRIME unless exists $prime_map->{(substr($number, -$_))};
    }
    #print join(",",@primes),"\n";
    print "$prime is tractable\n";
    $sum += $prime;
}
print "SUM: $sum\n";
