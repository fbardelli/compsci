use strict;
my @primes = (2);
my $num = 2;
my $primes = @primes;
my %primes = ();
NUM: while($num < 100_000){
  #prime if it does not divide evenly into seen primes
  $num++;
  my $sqrt = sqrt($num);
  for my $p (@primes) {
      last if $p > $sqrt;
      next NUM if $num % $p == 0;
  }
  push @primes,$num;
  $primes{$num} = 1;
  $primes{-$num} = 1;
  $primes++;
}
print "done building primes\n";

my $max_n = 0;
my $min_n = 0;
my $max_winner = {};
use constant MAX => 1000;
for $a ( (-(MAX))..(MAX) ){
    for $b ((-(MAX))..(MAX)){
        for my $n(0..1000){
            my $answer = (($n**2) + ($a*$n) + ($b));
            last if ! exists $primes{$answer};
            if ($n > $max_n){
                $max_n = $n;
                $max_winner = { a=>$a, b=>$b, max=>$max_n};
            }
        }
    }
}

printf("%d * %d = %d\n", $max_winner->{a}, $max_winner->{b}, $max_winner->{a}*$max_winner->{b});

