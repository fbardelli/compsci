use strict;
my @factorals = (0,1,2);

for my $i (3..9){
    $factorals[$i] = $factorals[$i-1] * $i;
}
my $highest = 1;
my $pow_10 = 1;
while( (10**$pow_10) < ($factorals[9]*$pow_10)){
    print 10**$pow_10 . " < "  . $factorals[9]*$pow_10 . "\n"; 
    $pow_10++;
}
$highest = $factorals[9]*$pow_10;

for my $i (3..$highest){
    my @digits = split(//,"$i");
    my $sum = 0;
    for my $j (@digits){
        $sum += $factorals[$j];
    }
    if ($sum == $i){
        print "$i\n";
    }
     
}
