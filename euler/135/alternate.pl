use lib '../lib/perl/';
use Euler::Primes;
my $prime_list = Euler::Primes::get_prime_map({maximum => 999999});
use Data::Dumper;
warn Dumper $prime_list;
sub is_prime{
    my $n=shift;
    return exists $prime_list->{$n};
}
 
$nmax = 55992;
$s = 0;
$inc = 3;
for ( my $n = 3; $n < $nmax; $n+=4){
    if(is_prime($n)){
        $s += $inc;
    }
    if( is_prime($n+2)){
        $s += ($inc-1);
    }

    if ($n>int($nmax/16)){
        $inc=2;
    }
    if ($n>int($nmax/4)){
        $inc=1;
    }
}

print "Answer to PE135 = $s \n";
