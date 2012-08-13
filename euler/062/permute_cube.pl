use strict;
use bigint;

my $x = {};
my $n = 1;
while(1){
    my $cube = $n**3;
    my $sorted = join( "", sort { $a <=> $b } split(//,$cube));
    #print "$n:$cube:$sorted\n";
    if(! exists $x->{$sorted}){
        $x->{$sorted} = [];
    }
    push(@{$x->{$sorted}},$cube);
    if(length(@{$x->{$sorted}} == 5)){
        print join ",",@{$x->{$sorted}};
        print "\n";
        last;
    }
    $n++;
}

