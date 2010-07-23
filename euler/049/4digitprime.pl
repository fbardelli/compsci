use strict;
use constant TOP_NUM => 10_000;
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
}

my %perms;
for my $p (@primes){
    next if $p < 1000;
    my @digits = split //, "$p";
    my $key = join " ", sort @digits;
    if(! exists $perms{$key}){
        $perms{$key} = [];
    }
    push(@{$perms{$key}}, $p)
}

use Data::Dumper;

for my $pm (keys %perms){
    if(scalar(@{$perms{$pm}}) < 3){
        delete $perms{$pm};
    }
}

for my $pm (keys %perms){
    my @values = @{$perms{$pm}};
    my @diffs;
    my %offset;
    while ( my $top = pop @values){
        for my $v (@values){
          my $diff = ($top - $v);
          if (!exists $offset{$diff}){
            $offset{$diff} = {};
          }
          $offset{$diff}{$top}++;
          $offset{$diff}{$v}++;

          push @diffs, "$top - $v = ".($top-$v);
          if(scalar keys(%{$offset{$diff}}) > 2){
              for my $k (keys %{$offset{$diff}}){
                if ($offset{$diff}{$k} > 1){
                    print Dumper $perms{$pm};
                    print "\n",join("\n",@diffs),"\n";
                }
              }
          }
        }
    }
}
print scalar keys %perms;
