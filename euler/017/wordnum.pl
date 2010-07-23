my %words = (
   1 => "one", 2 => "two", 3 => "three",4 => "four",5 => "five",
   6 => "six", 7 => "seven", 8 => "eight", 9 => "nine", 10 => "ten",
   11 => "eleven", 12 => "twelve", 13 => "thirteen", 14 => "fourteen", 15 => "fifteen",
   16 => "sixteen", 17 => "seventeen", 18 => "eighteen", 19 =>"nineteen", 20 => "twenty",
   30 => "thirty", 40 => "forty", 50 => "fifty", 60 => "sixty", 70 => "seventy", 80 => "eighty",
   90 => "ninety", 100 => "hundred", 1000 => "thousand"
);

for my $i (1..1000){
    my $small_num = $i % 100;
    my $big_num   = int($i / 100);
    print("$big_num:$small_num\n");
    $string = "";
    if($big_num){
        my $thousands = int($big_num / 10);
        my $hundreds  = $big_num % 10;
        if($thousands){
            $string .= $words{$thousands}." ".$words{1000};
        }
        if($hundreds){
            $string .= (length $string?" ":""). "$words{$hundreds} $words{100}"
        }
    }
    if($small_num){
        if($small_num>20){
        }else{
        }
    }
    print "$string";
}
