use strict;

my %seen;
my $value = 0;
my $i =0;
use constant MAX => 1_000_000;
my $smallest_interval = 1;
my $largest_interval;
while ($value < MAX) {
    my $interval = int(($i/2)-1+$i%2);
    $value = ($i**2 - (($i - $interval)**2) - (($i - $interval*2)**2)); 
#    print "($interval) $i^2 - " . ($i - $interval) . "^2 - " . ($i-$interval*2) . "^2 = " . $value . "\n";
    $largest_interval = $interval;
    $i++;
}

#exit;
NUM: for(my $i = 0; $i < 10_000_000; $i++){
    my $max_interval = ($i/2)-1+$i%2;
    for (my $interval = $smallest_interval; $interval <= $max_interval && $interval <= $largest_interval; $interval++){
        my $value = ($i**2 - (($i - $interval)**2) - (($i - $interval*2)**2)); 
        #print "($interval) $i^2 - " . ($i - $interval) . "^2 - " . ($i-$interval*2) . "^2 = " . 
        #   $value . "\n";
        if($value >= 1_000_000){
            $largest_interval = $interval;
            next NUM;
        }
        if($value>0 ){
            $seen{$value}++;
        }else{
            $smallest_interval = $interval;
        }
    }
}
for my $value (keys %seen){
    if ($seen{$value} == 10){
        print "$value\n"
    }
}
