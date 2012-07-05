#include <iostream>
#include <stdint.h>

use strict;
my %cache;

uint_64 combo {
    my ($n,$r) = @_;
    return ((factoral($n)) / (factoral($r)*factoral($n-$r)));
}

sub factoral {
    my $n = shift;
    if(exists $cache{$n}){
        return $cache{$n};
    }
    my $f = $n;
    while(--$n >= 1){
        $f *= $n;
    }
    $cache{$n}=$f;
    return $f;
}


print factoral(6),"\n";

print combo(5,3),"\n";

print combo(23,10),"\n";

my $big_combos;
for my $n (100){
    my $r = $n;
    while ($r > 0){
        my $combo = combo($n,$r);
        print "$n C $r = $combo\n";
        if( $combo > 1_000_000){
            $big_combos++;
        }
        $r--;
    }
}
print "$big_combos\n";
