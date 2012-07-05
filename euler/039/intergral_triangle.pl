use strict;
use Data::Dumper;
my %p;

for ( my $a = 1; $a < 500; $a++ ){
    for ( my $b = 1; $b < 500; $b++ ){
        my $c = sqrt( $a*$a + $b*$b);
        my $t = $a+$b+$c;
        if ( ($t <= 1000) &&  ($c == int($c)) ){
#            print "{ $a, $b, $c} = $t\n";
            if(! exists $p{$t}){
                $p{$t} = {};
            }
            my @array = ($a,$b,$c);
            @array = sort @array;
            $p{$t}->{(join ":", @array)} = [$a,$b,$c];
        }
    } 
}

my $max = 0;
my $max_p;
for ( keys %p){
    my $num_triplets = scalar keys %{$p{$_}};
    if($num_triplets > $max){
        $max = $num_triplets;
        $max_p = $_;
    }
}

#warn Dumper $p{$max_p};

print "$max_p has $max solutions";
