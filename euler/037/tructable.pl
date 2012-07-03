use lib '../lib/perl/';
use Euler::Primes;
use Data::Dumper;

warn Dumper Euler::Primes::get_prime_map({maximum => 100, as_list => 1});

