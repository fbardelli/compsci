use constant TOP_NUM => 2_000_000;
my $num = 2;
my @primes = ($num);
my $sum = $primes[0];
NUM: while ($num < TOP_NUM ){
  #prime if it does not divide evenly into seen primes
  $num++;
  my $sqrt = sqrt($num);
  for my $p (@primes) {
      last if $p > $sqrt;
      next NUM if $num % $p == 0;
  }
  push @primes,$num;
  $sum += $num;
}

print $sum,"\n";
