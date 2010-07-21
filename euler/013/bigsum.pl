use strict;
use IO::File;

my $sum = 0;
my $file = IO::File->new("numbers.txt");
while ( my $line = <$file>){
    chomp $line;
    $sum += substr($line,0,11);
}
print substr($sum,0,10),"\n";
