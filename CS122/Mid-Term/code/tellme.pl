use strict;
use warnings;

# Frank Mock
# CS 122 Midterm 1
# #1 Chapter 5 Problem 6

# Issue warning if no command line argument
if(scalar @ARGV < 1) {die "Usage: $0 filename\n";}

#get the file name entered at the command line
my $file = $ARGV[0];

#open the file for reading
open(my $fh, "<", $file) or die "Could not open file $file: $!";

#place the contents of the file in an array
my @datebook = <$fh>;

#print salary, name, phone
foreach(@datebook)
{
	my @line = split(":",$_);
	print"Salary: $line[4]";
	print"Name: $line[0]\n";
	print"Phone: $line[1]\n";
	print"\n";
}