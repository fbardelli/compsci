use strict;
use constant TOP_NUM => 1_000_000;
my $num = 2;
my @primes = ($num);
my %primes = ($num => 1);
my %circulars = ($num => 1);
my $sum = $primes[0];
NUM: while ($num < TOP_NUM ){
    if( ($num % 50_000) == 0){
        print "processing $num of " . TOP_NUM ."\n"
    }
    #prime if it does not divide evenly into seen primes
    $num++;
    my $sqrt = sqrt($num);
    for my $p (@primes) {
        last if $p > $sqrt;
        next NUM if $num % $p == 0;
    }
    push @primes, $num;
    $primes{$num} = 1;
    my $nlength = length("$num");
    if( $nlength == 1){
        $circulars{$num} = 1;
    } else {
        if ( "$num" !~ /[2|4|5|6|8|0]/){
            my @rotations = ($num);
            my $currnum = $num;
            for(my $i = 1; $i < $nlength; $i++){
                $currnum = substr($currnum,1,$nlength-1).substr($currnum,0,1);
                push @rotations, $currnum;
            }
            @rotations = sort @rotations; 
            if($num == $rotations[-1]){
                my @p = grep { exists $primes{$_} }@rotations;
                if(@p == @rotations){
                    map {$circulars{$_}++} @rotations;
                }
            }
        }
    }
}

print join(" ", sort {$a <=> $b } keys %circulars),"\n";
print scalar(keys %circulars), "\n";
