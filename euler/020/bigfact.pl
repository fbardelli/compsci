use strict;
use Math::BigInt;

my $bigfact = Math::BigInt->new("100");
for (my $n = 1; $n <= 99; $n++){
  $bigfact->bmul($n);
  print $bigfact,"\n";
}
my $sum = 0;
$sum += $_ for split //, $bigfact->bstr();
print $sum,"\n";
