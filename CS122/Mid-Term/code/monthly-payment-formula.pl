use strict;
use warnings;

# CS122 Midterm 1, Frank Mock
# #2 Chapter 6 Problem 11

my $p = 0;  # principal amnount borrowed 
my $r = 0;  # periodic interst rate
my $n = 0; # total number of payments
my $A = 0;  # periodic payment amount

#Get input for calculation from the user
print"Amortization Payment Calculator\n";
print"Enter loan amount: ";
$p = <STDIN>;
print"Enter the annual interest rate ";
$r = <STDIN>;
print"Enter number of monthly payments. (ie. 5 years = 60 months)";
$n = <STDIN>;

$r = ($r/12)/100; #convert $r into rate per period

#calulate the loan amount
$A = $p * (($r * (1 + $r)**$n)/(((1 + $r)**$n)-1));

printf("Your monthly payment will be \$%.2f", $A); 


