#!/usr/bin/perl
use Math::BigInt;
use strict;
 
my $sum = Math::BigInt->new("0");
for(1..1000){
  $sum->badd(Math::BigInt->new($_)->bpow($_))
} 
print $sum->bmod(1e10),"\n";
