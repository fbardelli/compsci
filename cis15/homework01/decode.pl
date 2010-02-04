use Encode qw( from_to is_utf8 );
use File::Slurp qw(slurp);
my $data = slurp('hearts.cpp');
from_to($data, "utf8","iso-8859-1" );
print $data;
