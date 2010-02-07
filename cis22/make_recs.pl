use strict;
use IO::File;

my $file = IO::File->new("master.dat");

my @items = (
  {name => "Power Coupling",id=>1001,price=>45.99},
  {name => "Emitter Matrix",id=>1015,price=>11.15},
  {name => "Inertial Compensator",id=>2002,price=>23.05},
  {name => "Alluvial Dampener",id=>2150,price=>33.49},
  {name => "Crystal Oscillator",id=>2733,price=>17.49},
  {name => "Field Energizer",id=>2805,price=>61.37},
  {name => "Stabilizing Ring",id=>3001,price=>4.50},
  {name => "Heuristic Processor",id=>3002,price=>104.05},
  {name => "Vocabulator",id=>3118,price=>22.35},
  {name => "Restraining Bolt",id=>2150,price=>38.98},
  {name => "Adv Shield Disruptor",id=>2150,price=>212.10}
);
#for my $i (@items){
#print $i->{name}, " " ,length $i->{name},"\n";
#}
my @ids;
while (my $line = <$file>){
  my ($id,$name,$balance) = split("\t",$line);
  push @ids, $id;
}
my %seen_ids;

for my $id (sort {$a<=>$b} @ids) {
  my $num_orders = 0;
  my $num_payments = 0;
  for(1..(3+ int(rand 4))){
    my $item = $items[int(rand(@items))];
    my $transaction_id = (1000+int rand(9000));
    while(exists $seen_ids{$transaction_id}){
      $transaction_id = (1000+int rand(8999));
    }
    $seen_ids{$transaction_id} = 1;
    if(int rand(3) && ($num_orders < 4 || $num_payments > 3) ){
      print join("\t","0",$id,$transaction_id,$item->{name},int(1+rand(10)),sprintf("%3.2f",$item->{price})),"\n";
      ++$num_orders;
    } else {
      print join("\t","P",$id,$transaction_id,sprintf("%3.2f",20+rand(700))),"\n";
      ++$num_payments;
    }
  }
}
