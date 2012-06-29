use constant MAX_SIZE => 1001;
#use constant MAX_SIZE => 100000001;
$sum = 1;
$counter = 1;
for($i = 2; $i < MAX_SIZE; $i += 2){
    for($j = 0; $j < 4; $j++){
        $counter += $i;
        $sum += $counter;
    }
}
print  $sum,"\n";

