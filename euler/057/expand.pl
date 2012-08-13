use bigint;
# ^1 ^2 ^5 ^12
#   +4 +10 +24 +58
# 3  7  17  41  99
#   +3 +7  +17 +41
# 2  5  12  29  70
my @seq = (1, 1);
my $n = 2;
for ( 1..1002){
    push @seq, 2*$seq[$n-1] + $seq[$n-2];    
    $n++;
}

my $count = 0;
for(2..1001){
    my $num = $seq[$_];
    my $denom = (($seq[$_]+$seq[$_-1])/2);
    #print length($num), ":", length($denom), "\n";
    if(length($num) > length($denom)){
        $count++
        #print "$num/$denom\n"
    }
}
print "$count\n";
