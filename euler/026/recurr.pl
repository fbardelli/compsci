use Math::BigFloat;
use Data::Dumper;
use Tree::Suffix;
use strict;
my $longest_cycle = 0;
use constant SCALE => 5_000;
for my $i (1..1000){
    long_div(1,$i);
}

sub long_div {
    my ($numerator, $denominator)  = @_;
    my @result;
    my %seen = ();
    if($numerator == $denominator){
        return 1;
    }
    my $limit = 0;
    do {
        $limit++;
        my $shift = 0;
        while($numerator < $denominator){
            $numerator *= 10;
            if($shift){
                $limit++;
                push @result, 0;
            }
            $shift++;
        }
        my $result = int($numerator / $denominator);
        push @result, $result;
        ($numerator) = ($numerator - ($denominator * ( int($result) )));
        if(! exists $seen{$numerator} ){
            $seen{$numerator} = length(@result);
        }else{
            my @resultcopy = @result;
            my $cycle = join("",splice(@resultcopy,$seen{$numerator}));
            if(length($cycle) > $longest_cycle){

                my $f = Math::BigFloat->new("1");
                $f->div_scale(SCALE);
                print sprintf("(1/$denominator)\t%s\n",$f->bdiv($denominator));
                print "$denominator\'s cycle = $cycle";
                print "\n length( " , length($cycle),")\n";
                $longest_cycle = length($cycle);
            }
            return "0.".join "",@result;
        }
    } while ( $numerator != 0 && $limit <= SCALE );
    return "0.".join "",@result;
}
