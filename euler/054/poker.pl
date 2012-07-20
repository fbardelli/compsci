package Poker::Hand;
use strict;

use overload '""' => \&stringify, '0+' => \&numify, '<=>' =>\&compare;

sub new {
    my ($class,$cards) = @_;
    my $self = {
        cards => $cards,
        royal_flush => 0,
        straight_flush => 0,
        straight => 0,
        flush => 0,
        full_house => 0,
        two_of_a_kind => 0,
        two_pair => 0,
        three_of_a_kind => 0,
        four_of_a_kind => 0,
        high_pair => 0,
        low_pair => 0
    };
    bless $self,$class;
    $self->analyze();
    return $self;
}

=pod

=head1 Scoring overview

 offset:     33  32  31  30  29  28  24  20  16 12  8  4  0 
 bits:       1   1   1   1   1   1   4   4   4  4   4  4  4
 condition: [SF][4K][FH][FL][ST][3K][HP][LP][H][MH][M][ML][L]
 HP = High pair, either a 3 of a kind, Full House 3 of a kind, a 4 of a kind, or the higher value of 2 pair
 LP = Low pair, either a 2 of a kind, the lower of 2 pair, or the 2 of a kind in a full house
 Royal Flush is just a straight flush with a higher high card, so needs no flag

=cut

sub score {
    my $self = shift;
    #using a 34 character string to represent the bits
    return sprintf( ("%b"x6).("%04b"x7),
        $self->{straight_flush} % 2,
        $self->{four_of_a_kind} % 2, 
        $self->{full_house} % 2,
        $self->{flush} % 2,
        $self->{straight} % 2,
        $self->{three_of_a_kind} % 2,
        $self->{high_pair} % 16,
        $self->{low_pair} % 16,
        $self->cards->[0]->value % 16,
        $self->cards->[1]->value % 16,
        $self->cards->[2]->value % 16,
        $self->cards->[3]->value % 16,
        $self->cards->[4]->value % 16
    );

=for comment
    #This one only works on 64-bit perls, requires a 34-bit int   
    return (
        $self->cards->[4]->value +
        ($self->cards->[3]->value << 4) +
        ($self->cards->[2]->value << 8) +
        ($self->cards->[1]->value << 12) +
        ($self->cards->[0]->value << 16) +
        ($self->{low_pair} << 20) +
        ($self->{high_pair} << 24) +
        ( ($self->{three_of_a_kind} ? 1 : 0) << 28) +
        ( ($self->{straight} ? 1 : 0) << 29) +
        ( ($self->{flush} ? 1 : 0) << 30) +
        ( ($self->{full_house} ? 1 : 0) << 31) +
        ( ($self->{four_of_a_kind} ? 1 : 0) << 32) +
        ( ($self->{straight_flush} ? 1 : 0) << 33)
    );
=cut

}

sub cards {
    my $self = shift;
    return $self->{cards};
}

sub analyze {
    my $self = shift;
    my $suits = {};
    my $values = {};
    $self->{cards} = [ 
        map{ $_->[0] } 
        sort{ $b->[1] <=> $a->[1] } 
        map{ [$_, $_->value] }
        @{$self->cards}
    ];
    for my $card (@{$self->cards}){
       $suits->{$card->suit}++;
       my $suit_count = $suits->{$card->suit};
       if($suit_count == 5){
         $self->{flush} = 1;
       }

       $values->{$card->value}++;
    }

    my $straight = 0;
    my $high = $self->cards->[0]->value;
    my $medh = $self->cards->[1]->value;
    my $med  = $self->cards->[2]->value;
    my $medl = $self->cards->[3]->value;
    my $low  = $self->cards->[4]->value;
    if( $high-1 == $medh &&
        $medh-1 == $med &&
        $med-1 == $medl &&
        $medl-1 == $low){
            $self->{straight} = 1;
            if($self->{flush}){
                $self->{straight_flush} = 1;
                if($self->cards->[0]->face eq 'A'){
                    $self->{royal_flush} = 1;
                }
            }
    } 
    my $max = 0;
    for my $v (keys %$values){
        if($values->{$v} > $max){
            $max = $values->{$v};
        }
        if($values->{$v} == 2){
            if(!$self->{low_pair}){
                $self->{low_pair} = $v;
            }else{
                if($values->{$v} > $self->{low_pair}){
                    $self->{high_pair} = $v;
                }else{
                    $self->{high_pair} = $self->{low_pair}; 
                    $self->{low_pair} = $v;
                }
            }
        }
        if($values->{$v} > 2){
            $self->{high_pair} = $v;
        }
    }

    if($max == 4){
        $self->{four_of_a_kind} = 1;
    } elsif($max == 3) {
        $self->{three_of_a_kind} = 1;
        if($self->{low_pair}){
            $self->{full_house} = 1;
        }
    } elsif($max == 2) {
        if($self->{high_pair}){
            $self->{two_pair} = 1;
        }else{
            $self->{two_of_a_kind} = 1;
        }    
    }
}

sub stringify {
    my $self = shift;
    return "[". join(",",@{$self->cards})."] " . $self->score() . "";
}

sub numify {
    my $self = shift;
    return $self->score();
}

sub compare {
    my($self, $cmp) = @_;
    return $self->score() cmp $cmp->score();
}
1;

package Poker::Card;
use strict;
use overload '""' => \&stringify;
use constant VALUE_MAP => {
    2 => 2,  3 => 3,  4 => 4,  5 => 5,  
    6 => 6,  7 => 7,  8 => 8,  9 => 9,
    T => 10, J => 11, Q => 12, K => 13,
    A => 14
};

sub new {
    my ($class,$description) = @_;
    my $face = substr($description, 0, 1);
    my $suit  = substr($description, 1, 1);
    my $self = {
        face => $face,
        suit => $suit
    };
    bless $self,$class;
    return $self;
}

sub suit {
    my $self = shift;
    return $self->{suit};
}

sub face {
    my $self = shift;
    return $self->{face};
}

sub value {
    my $self = shift;
    return VALUE_MAP->{$self->{face}};
}

sub stringify {
    my $self = shift;
    return $self->face . $self->suit;
}

1;

package main;
use strict;
use IO::File;

my $file = IO::File->new("poker.txt") or die ($!);

$/ = "\r\n";
my $player1_wins = 0;
while( chomp(my $line = <$file>) ){
    my @p1cards = map { Poker::Card->new($_) } split / /,$line;
    my @p2cards = splice(@p1cards,-5);
    my $p1hand = Poker::Hand->new(\@p1cards);
    my $p2hand = Poker::Hand->new(\@p2cards);
    if($p1hand > $p2hand){
        $player1_wins++;
        print "player1 $p1hand beats player2 $p2hand\n";
    }else{
        print "player2 $p2hand beats player1 $p1hand\n";
    }
}
print "player 1 wins $player1_wins\n";

