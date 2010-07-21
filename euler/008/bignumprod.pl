use strict;
use IO::File;

my $sum = 0;
my $file = IO::File->new("hugenum.txt");
my @numbers;
while ( my $line = <$file>){
    chomp $line;
    push @numbers, split //, $line;
}
my $max_prod = 0;
my @max_seq;
for my $i (0..@numbers-5){
  my $prod = 1;
  for my $digit (@numbers[$i..$i+4]){
    $prod *= $digit;
  }
  if($prod > $max_prod){
      $max_prod = $prod;
      @max_seq = (@numbers[$i..$i+4]);
  }
}

print "largest product is $max_prod the product of ", join(",",@max_seq),"\n";
