use strict;
use Math::BigInt;
my %distinct = ();

for my $a(2..100){
    for my $b(2..100){
        my $x = Math::BigInt->new($a);
        $distinct{ ($x->bpow($b)) } = 1;
    }
}

print scalar( keys %distinct),"\n"
