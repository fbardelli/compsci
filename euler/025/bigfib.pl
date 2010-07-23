use strict;
use Math::BigInt;
use constant MAX_SIZE => 1000;
my $last = Math::BigInt->new("1");
my $current = Math::BigInt->new("1");
my $nthterm = 2;
for(;;){
    $nthterm++;
    ($last,$current) = ( $current->copy, $current->badd($last));
    if (length($current->bstr()) >= 1000){
        print $nthterm, " : ", $current->bstr(), "\n";
        last;
    }
}
