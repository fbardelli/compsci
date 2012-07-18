=pod
RF ([RF]) 
    -> SF ( [SF,Highest] )
        -> ( [4K,4K,Remander] ) 
            -> ( [FH,3K,2K] ) 
                -> ( [FL,H,MH,M,ML,L] ) 
                    -> ( [ST,Highest] ) 
                        -> ( [3K,3K,High,Low] ) 
                            -> ( [2K2,2KH,2KL,Remainder] ) 
                                -> ( [2K,2K,H,M,L] )
                                    -> ( [HC, H, MH, M, ML, M])
 30  29  28  27  26  25   24   20  16 12  8  4  0 
 1   1   1   1   1   1    4    4   4  4   4  4  4
[SF][4K][FH][FL][ST][3K][P2H][P1L][H][MH][M][ML][L]

{
    value => { 2=>N,3=>N,4=>N,5=>N,6=>N,7=>N,8=>N,9=>N,T=>N,J=>N,Q=>N,K=>N,A=>N},
    suits => { S=>N,C=>N,D=>N,H=>N},
    cards => [ high, medhigh, med, medlow, low],
    royal => ( isStraight && isFlush && high == A)
    straight => T|F
    flush => T|F
    pairs => (0-2) [high,low]
    three => (0-1) [high]
    four => (0-1) [high]
}
=cut
package Hand;
use constant VALUE_MAP => {
    2 => 2,
    3 => 3,
    4 => 4,
    5 => 5,
    6 => 6,
    7 => 7,
    8 => 8,
    9 => 9,
    T => 10,
    J => 11,
    Q => 12,
    K => 13,
    A => 14
};
=pod
 30  29  28  27  26  25   24   20  16 12  8  4  0 
 1   1   1   1   1   1    4    4   4  4   4  4  4
[SF][4K][FH][FL][ST][3K][P2H][P1L][H][MH][M][ML][L]
=cut

use overload '""' => \&stringify;
sub new {
    my ($class,$cards) = @_;
    my $self = {
        cards => $cards,
        straight => 0,
        flush => 0,
        full_house => 0,
        three_of_kind => 0,
        pairs => 0,
        high_pair => 0,
        low_pair => 0
    };
    bless $self,$class;
    $self->analyze();
    return $self;
}

sub analyze {
    my $self = shift;
    my $suits = {};
    my $values = {};
    $self->{cards} = [ 
        map{ $_->[0] } 
        sort{ VALUE_MAP->{$b->[1]} <=> VALUE_MAP->{$a->[1]} } 
        map{ [$_, $_->value] }
        @{$self->{cards}}
    ];
    for $card (@{$self->{cards}}){
       $suits->{$card->suit}++;
    }
    for my $s (keys %$suits){
        if($suits->{$s} == 5){
            print "found a flush $self\n";
        }
    }
    my $high = $self->{cards}->[0]->value;
    my $medh = $self->{cards}->[1]->value;
    my $med  = $self->{cards}->[2]->value;
    my $medl = $self->{cards}->[3]->value;
    my $low  = $self->{cards}->[4]->value;
    if( $high-1 == $medh &&
        $medh-1 == $med &&
        $med-1 == $medl &&
        $medl-1 == $low){
            print "found a straight $self\n";
    } 
}
sub stringify {
    my $self = shift;
    return "[". join(",",@{$self->{cards}})."]";
}
1;

package Card;
use overload '""' => \&stringify;

sub new {
    my ($class,$description) = @_;
    my $value = substr($description, 0, 1);
    my $suit  = substr($description, 1, 1);
    my $self = {
        value => $value,
        suit => $suit
    };
    bless $self,$class;
    return $self;
}

sub suit {
    my $self = shift;
    return $self->{suit};
}

sub value {
    my $self = shift;
    return $self->{value};
}

sub stringify {
    my $self = shift;
    return $self->value . " of " . $self->suit;
}

1;

package main;
use strict;
use IO::File;

my $file = IO::File->new("poker.txt") or die ($!);

$/ = "\r\n";
while( chomp(my $line = <$file>) ){
    #print "all: $line";
    my @p1cards = map { Card->new($_) } split / /,$line;
    my @p2cards = splice(@p1cards,-5);
    my $p1hand = Hand->new(\@p1cards);
    my $p2hand = Hand->new(\@p2cards);
    #print " p1: $p1hand p2: $p2hand\n";
}

