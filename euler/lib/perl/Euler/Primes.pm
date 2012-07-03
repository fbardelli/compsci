package Euler::Primes;
use strict;

sub get_prime_map {
    my ($args) = shift;
    use Data::Dumper;
    warn Dumper $args; 
    $args ||= {};
    if(!(defined $args->{maximum}) || $args->{maximum} !~ /^\d+$/){
        die "you must provide an integer maximum";
    }   
    my @primes;
    my %primes;
    my $num = 1;
    NUM: while ($num < $args->{maximum} ){
        #prime if it does not divide evenly into seen primes
        $num++;
        my $sqrt = sqrt($num);
        for my $p (@primes) {
            last if $p > $sqrt;
            next NUM if $num % $p == 0;
        }
        push @primes, $num;
        $primes{$num} = 1 ;
    }
    return $args->{as_list} ? \@primes : \%primes;
}

1;
