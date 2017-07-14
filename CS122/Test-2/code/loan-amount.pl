use strict;
use warnings;

# Frank Mock  CS 122   Test 2
# Chapter 11,  Problem 4
# This program provides a function that calculates and
# returns the monthly payment on a loan assuming a
# conventional loan where the interest is compounded
# monthly

# Get the loan amount from the user
print"What is the loan amount?";
chomp(my $amount = <STDIN>);

# Get the interest rate from the user
print"What is the annual interest rate (from 1 to 100)?";
chomp(my $rate = <STDIN>);

# Get the number of years of the loan from the user
print"Enter the number of years of the loan";
chomp(my $years = <STDIN>);

# Define variables that hold the value of loan details
my $P = $amount; # principal, the initial amount of the loan
my $I = $rate; 		# The annual interest rate ( from 1 to 100 )
my $L = $years;		# The length (in years) of the loan

# Hash that contains the loan info to pass to function
my %loanInfo = ("Principal" => $P,
				"Interest" => $I,
				"Length"   => $L);
				
# This function takes a hash that contains loan details as a
# parameter and returns the monthly payment amount
sub calcLoanPayment
{
	my %h = @_;
	my $p = $h{'Principal'};
	my $i = $h{'Interest'};
	my $l = $h{'Length'};
	my $J = $i/(12*100); # Monthly interest rate in decimal form
	my $N = $L*12; # Number of months over which the loan is amoritzed
	my $M = $p*($J/(1 - (1 + $J)**-$N));	
	return $M;
}

# Call the function calcLoanPayment and assign return value to variable
my $monthly_payment = calcLoanPayment(%loanInfo);

# Print the monthly payment returned from the function
printf("The monthly payment for a 3o year loan of $P at a rate of $I percent is \$%7.2f", $monthly_payment);
