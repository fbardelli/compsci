use strict;
use IO::File;
use Data::Dumper;

my $file = IO::File->new("passes.txt");

my %digits;
while(my $line = <$file>){
    chomp $line;
    my @chars = split //, $line;
    for my $c (@chars){
        if(! exists $digits{$c}){
            $digits{$c}=0;
        }
    }
    $digits{$chars[0]}+=100;
    $digits{$chars[1]}+=10;
    $digits{$chars[2]}+=1;
}
warn Dumper \%digits;

my @digits = sort {$digits{$b} <=> $digits{$a} } keys %digits;
print join("",@digits),"\n";
