use constant TOP => 20;
my @primes;


NUM: for my $num (2..TOP){
  for my $p(@primes) {
      next NUM if $num % $p == 0;
  }
  push @primes, $num;
}

$product = 1;

for my $p (@primes){
    my $i = 1;
    my $pn = $p;
    while($pn*$p < TOP){
        $pn *= $p;
    }
    $product *= $pn;
}
print "$product\n";
