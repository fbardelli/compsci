use strict;

my %seen;
for(my $i = 0; $i <100; $i++){
    my $max_interval = ($i/2)-1+$i%2;
    for (my $interval = 1; $interval <= $max_interval; $interval++){
        my $value = ($i**2 - (($i - $interval)**2) - (($i - $interval*2)**2)); 
        print "($interval) $i^2 - " . ($i - $interval) . "^2 - " . ($i-$interval*2) . "^2 = " . 
           $value . "\n";
        if($value>0 && $value < 1_000_000){
            $seen{$value}++;
        }
    }
}
for my $value (keys %seen){
    if ($seen{$value} == 10){
        print "$value\n"
    }
}
