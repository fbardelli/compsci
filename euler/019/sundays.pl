use strict;
use DateTime;
my $dt = DateTime->new( year => 1901, month => 1, day => 1 );
my $sundays = 0;
while($dt->year < 2001){
  ++$sundays if $dt->day_of_week == 7;
  printf("%s %s %d, %d\n",$dt->day_name,$dt->month_name, $dt->day_of_month, $dt->year);
  $dt->add(months=>1);
}
print("1st day Sundays: $sundays\n");
