
my @primes = (2);
my $num = 2;
my $primes = @primes;
NUM: while ($primes < 10001){
  #prime if it does not divide evenly into seen primes
  $num++;
  my $sqrt = sqrt($num);
  for my $p (@primes) {
      last if $p > $sqrt;
      next NUM if $num % $p == 0;
  }
  push @primes,$num;
  $primes++;
}

print $primes[-1],"\n";
