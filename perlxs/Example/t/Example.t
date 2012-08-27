# Before `make install' is performed this script should be runnable with
# `make test'. After `make install' it should work as `perl Example.t'

#########################

# change 'tests => 1' to 'tests => last_test_to_print';

use strict;
use warnings;

use Test::More tests => 3;
BEGIN { use_ok('Example') };

my $ret = Example::print_hello();
is($ret, 6);
is(Example::treble(10),30);
#########################

# Insert your test code below, the Test::More module is use()ed here so read
# its man page ( perldoc Test::More ) for help writing this test script.

