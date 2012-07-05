use strict;
my %cache = {0 => 1};

sub combo {
    my ($n,$r) = @_;
    return ((factoral($n)) / (factoral($r)*factoral($n-$r)));
}

sub factoral {
    my $n = shift;
    if(exists $cache{$n}){
        return $cache{$n};
    }
    #return 1 if $n == 0;
    my $f = $n;
    while(--$n >= 1){
        $f *= $n;
    }
    $cache{$n}=$f;
    return $f;
}

my $big_combos = 0;
for my $n (1..100){
    my $r = $n;
    while ($r > 0){
        my $combo = combo($n,$r);
        #print "$n C $r = $combo\n";
        if( $combo > 1_000_000){
            $big_combos++;
        }
        $r--;
    }
}
print ">1,000,000 = $big_combos\n";
