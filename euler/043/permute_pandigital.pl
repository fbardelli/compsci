use Algorithm::FastPermute qw(permute);
use strict;
my @numbers = (1..9,0);
#my @numbers =(1406357289);
my $sum = 0;
permute{
    my $num = join "", @numbers;
    if($num >= 1023456789){
        if(substr($num,1,3) % 2 == 0 
            && substr($num,2,3) % 3 == 0
            && substr($num,3,3) % 5 == 0
            && substr($num,4,3) % 7 ==0
            && substr($num,5,3) % 11 == 0
            && substr($num,6,3) % 13 == 0
            && substr($num,7,3) % 17 == 0) {
                print "$num\n";
                $sum += $num;
        }
    }
} @numbers;
print "SUM: $sum\n";
