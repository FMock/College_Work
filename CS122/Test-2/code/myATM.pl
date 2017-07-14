use strict;
use warnings;

# Frank Mock CS 122 Test 2
# Chapter 13, Problems 2 and 4
# This program simulates ATM machine transactions

package Checking;

my $balance = 0; # Lexical private variable

# Returns the value of the private balance variable
sub get_balance
{
	return $balance;	
}

# Deposit increases the value of $balance
sub deposit
{
	my $amount = shift;
	$balance += $amount;
}

# withdraw reduces the value of $balance
sub withdraw
{
	my $amt = shift;
	$balance -= $amt;
}

# Write the current balance to file register.txt
sub saveBalance
{
	my $date = localtime(); # get the current date and time
	
	# open register file for writing
	open(my $fh, ">", "register.csv") || die "Could not save balance to file.";
	
	print $fh  "$balance,$date";
	close $fh;
}

# Get balance from the register.csv file
sub readBalanceRegister
{
	open(my $fh, "<", "register.csv") || die"Could not read balance from file.";
	#read each line of the register file into the @bal array
	chomp(my @bal = <$fh>);
	
	# First element is current balance from file
	my $line = $bal[0];
	
	# The balance and date are separated by a comma
	my @tokens = split(/,/, $line);
	
	# The first token is the balance from the file
	$balance = $tokens[0];
}



package main;

# Read the last balance saved to file
Checking::readBalanceRegister();

# menu sub routine displays a list of ATM choices
sub menu{
	print <<EOF;
	1. Deposit
	2. Withdraw
	3. Current Balance
	4. Exit
EOF
}

my $amt = 0;
my $choice = 3; # Default choice is Current Balance

# Prompt the user to make a selection until choice 4
# is selected.
while($choice != 4)
{
	menu;
	print"Please select (1 - 4) from the menu: ";
	chomp($choice = <STDIN>); # Save users input to variable $choice
	
	# Take action depending on the users choice
	if($choice == 1)
	{
		print"Enter deposit amount: ";
		chomp($amt = <STDIN>); # Save users input to variable $amt
		Checking::deposit($amt);
	}
	elsif($choice == 2)
	{
		print"Enter amount to withdraw:";
		chomp($amt =<STDIN>); # Save users input to variable $amt
		Checking::withdraw($amt);
	}
	elsif($choice == 3)
	{
		$amt = Checking::get_balance();
		print"The current balance is \$$amt\n";
	}
	else # End of program
	{
		# Save balance to file before exiting
		Checking::saveBalance();
		print"Goodbye";
	}
}
