use constant TOP => 20;

my @primes;
$product = 1;

NUM: for my $num (2..TOP){
  #prime if it does not divide evenly into seen primes
  my $sqrt = sqrt($num);
  for my $p(@primes) {
      last if $p > $sqrt;
      next NUM if $num % $p == 0;
  }
  push @primes,$num;
  my $i = 1;
  my $pn = $num;
  #get largest exponent of prime that is < TOP
  while($pn*$num < TOP){
      $pn *= $num;
  }
  $product *= $pn;
}

print "$product\n";
