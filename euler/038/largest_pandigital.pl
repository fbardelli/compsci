use strict;
sub is_pandigital {
    my ($i) = shift;
    my $combined = "$i";
    for(1..length($combined)){
        return 0 unless $combined =~ /$_/;
    }
    return 1;
}

sub contains_duplicates {
    my $number = shift;
    for(1..9){
        my $count = $number =~ s/$_/*/g;
        if($count > 1){
            return 1;
        }
    }
    return 0;
}

my $largest_pandigital = 0;
NUMBER: for my $number(1..99999){
    my $str = "";
    for my $digit(1..9){
        my $product = $number * $digit;
        $str .= $product;
        if(length($str) > 9 || contains_duplicates($str)){
            next NUMBER;
        }
        if($digit >= 2 && is_pandigital($str)){
            if(($str+0) > $largest_pandigital){
                $largest_pandigital = ( $str + 0);
                print "largest = ",
                    join("+",map { "($number * $_)" } (1..$digit)),
                    " = $largest_pandigital\n";
            }
        }

    }
}

