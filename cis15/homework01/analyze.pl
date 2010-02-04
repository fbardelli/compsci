use strict;

my $output;
my %freq;
my $total;
for(1..20_000){
  $output = qx{./hearts};
  for((split "\n", $output)[0..12]){
    $freq{$_}++;
    $total++;
  }
  if ( $_ % 10000 == 0){ print "processed $_ runs\n";}
}

my @ksorted = sort { $freq{$a} <=> $freq{$b} } keys %freq;
for ( @ksorted ){
  printf( "%15s : %07d : %5.2f%%\n", $_, $freq{$_}, ($freq{$_}/$total)*100);
}
