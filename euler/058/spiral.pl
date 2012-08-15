=cut
17 16 15 14 13
18  5  4  3 12
19  6  1  2 11
20  7  8  9 10
21 22 23 24 25

* 1r 1u *
2l * 2d *
2r * 1r 3u *
4l * 4d *
4r * 1r 5u *
6l 6d
=cut
use lib '../lib/perl/';
use Math::Prime::FastSieve;
use strict;
use Data::Dumper;
#my $prime_map = Euler::Primes::get_prime_map({maximum => 10_000_000});

my $sieve = Math::Prime::FastSieve::Sieve->new( 1_000_000_000 );
warn "done with primes\n";

my $n = 7;

my $n_sq = $n **2;
my $total = 0;
my $prime = 0;
my $average = 1;
my $num = 1;
my $step = 2;

while ($average > 0.1){
    for(1..4){
        if($sieve->isprime($num)){
            $prime++;
        }
        $total++;
        $num+=$step;
    }
    $step+=2;
    $average = $prime / $total;
    #print "$prime / $total = $average\n";
}
#print "[$num]";
print sqrt($num),"\n";
