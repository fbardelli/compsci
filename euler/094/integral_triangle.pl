my $end = 1e9/3;
print "$end\n";
$end = 100000;
for my $side (2..$end){
    $base1 = $side - 1;
    $base2 = $side + 1;
    for my $base ($base1,$base2){
        my $height = sqrt( ($side**2) - (($base*0.5)**2));
        my $area = (($base*0.5) * $height);
        #print "A($side,$side,$base) = $area\n";
        if ($area == int($area)){
            my $perimeter = $side + $sdie + $base;
            print "A($side,$side,$base) = $area\n";
            print "P($side,$side,$base) = $perimeter\n";
        }
    }

}
