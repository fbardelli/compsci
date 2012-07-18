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

use overload '""' => \&stringify;
sub new {
    my ($class,$cards) = @_;
    my $self = {
        cards => $cards,
        royal => 0,
        straight => 0,
        flush => 0
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
       $values->{$card->value}++;
    }
    my $flush = 0;
    for my $s (keys %$suits){
        if($suits->{$s} == 5){
            $flush = 1;
            #print "found a flush $self\n";
        }
    }
    my $straight = 0;
    my $high = VALUE_MAP->{$self->{cards}->[0]->value};
    my $medh = VALUE_MAP->{$self->{cards}->[1]->value};
    my $med  = VALUE_MAP->{$self->{cards}->[2]->value};
    my $medl = VALUE_MAP->{$self->{cards}->[3]->value};
    my $low  = VALUE_MAP->{$self->{cards}->[4]->value};
    if( $high-1 == $medh &&
        $medh-1 == $med &&
        $med-1 == $medl &&
        $medl-1 == $low){
            $straight = 1;
            if($flush){
                if($high eq VALUE_MAP->{'A'}){
                    print "found a royal flush $self\n";
                }else{
                    print "found a straight flush $self\n";
                }
            }else{
                print "found a straight $self\n";
            }
    } 
    if ( $flush && ! $straight){
                print "found a flush $self\n";
    }
    my $max = 0;
    my $pair_count = 0;
    for my $v (keys %$values){
        if($values->{$v} > $max){
            $max = $values->{$v};
        }
        if($values->{$v} == 2){
            $pair_count++;
        }
    }

    if($max == 4){
            print "found a 4 of a kind $self\n";
    } elsif($max == 3) {
            if($pair_count){
                print "found a FULL HOUSE $self\n";
            }else{
                print "found a 3 of a kind $self\n";
            }
    } elsif($max == 2) {
        if($pair_count == 2){
            print "found two pair $self\n";
        }else{
            print "found two of a kind $self\n";
        }    
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
    return $self->value . $self->suit;
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

