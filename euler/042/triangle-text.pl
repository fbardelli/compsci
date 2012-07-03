use strict;
use Data::Dumper;
use IO::File;

my $words = IO::File->new("words.txt");

my $word_text = <$words>;
my @word_array;
eval qq{
    \@word_array = ( $word_text );
};

my %triangle_numbers;
for my $i (0..1000){
   $triangle_numbers{(triangle($i))} = $i;
}

my $triangle_count = 0;
for my $word (@word_array){
    $word = uc($word);
    my $score = 0;
    for my $letter (split //,$word){
        $score += ( ord($letter) - 64);
    }
    if( exists $triangle_numbers{$score} ){
        $triangle_count++;
    }
}

print "TC: $triangle_count\n";

sub triangle {
    my $n = shift;
    return ((0.5*$n)*($n+1));
}
