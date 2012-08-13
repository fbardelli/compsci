use bigint;
my $count = 0;
for my $n (1..9){
    my $exp = 0;
    my $ne = $n ** $exp;
    while(length($ne) >= $exp){
        if(length($ne) == $exp){
            print "$n ** $exp = $ne\n";
            $count++;
        }
        $ne = $n ** ++$exp
    }
}
print "TOTAL: $count\n";
