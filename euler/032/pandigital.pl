my %seen;
for my $i (10..99){
    for my $j (100..999){
        is_pandigital($i,$j);
    }
}
for my $i (1..9){
    for my $j (1000..9999){
        is_pandigital($i,$j);
    }
}

sub is_pandigital {
    my ($i,$j) = @_;
    my $p = $i * $j;
    my $combined = "$i$j$p";
    if(length($combined) == 9){
        for(1..9){
            return unless $combined =~ /$_/;
        }
        if (! exists $seen{$p}){
            print "$i * $j = $p\n";
            $seen{$p}++;
        }else{
            print "SEEN $i * $j = $p\n";
        }
    }
}

my $total = 0;
for (keys %seen){
    $total += $_;
}
print "$total\n";
