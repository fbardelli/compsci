use strict;

my %seen;
my $value = 0;
my $i =0;
use constant MAX => 1_000_000;
while ($value < MAX) {
    my $interval = int(($i/2)-1+$i%2);
    $value = ($i**2 - (($i - $interval)**2) - (($i - $interval*2)**2)); 
    print "($interval) $i^2 - " . ($i - $interval) . "^2 - " . ($i-$interval*2) . "^2 = " . $value . "\n";
    $i++;
}

exit;
NUM: for(my $i = 0; $i <100; $i++){
    my $max_interval = ($i/2)-1+$i%2;
    for (my $interval = 1; $interval <= $max_interval; $interval++){
        my $value = ($i**2 - (($i - $interval)**2) - (($i - $interval*2)**2)); 
        print "($interval) $i^2 - " . ($i - $interval) . "^2 - " . ($i-$interval*2) . "^2 = " . 
           $value . "\n";
        if($value >= 1_000_000){
            next NUM;
        }
        if($value>0 ){
            $seen{$value}++;
        }
    }
}
for my $value (keys %seen){
    if ($seen{$value} == 10){
        print "$value\n"
    }
}
